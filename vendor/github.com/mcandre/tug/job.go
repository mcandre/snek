package tug

import (
	"log"
	"os"
	"os/exec"
	"strings"
)

// Job models a Docker muliti-image build operation.
type Job struct {
	// Debug can enable additional logging.
	Debug bool

	// Push can push cached buildx images to the remote Docker registry
	// as a side effect during builds.
	Push bool

	// Builder denotes a buildx builder.
	Builder string

	// LoadPlatform can load the image for a given platform
	// onto the local Docker registry as a side effect during builds.
	LoadPlatform *string

	// Platforms denotes the list of targeted image platforms.
	Platforms []Platform

	// OsExclusions skips the given operating systems.
	OsExclusions []string

	// ArchExclusions skips the given architectures.
	ArchExclusions []string

	// ListImageName can query the buildx cache
	// for any multi-platform images matching the given image name,
	// of the form name[:tag].
	ListImageName *string

	// ImageName denotes the buildx image artifact name,
	// of the form name[:tag].
	ImageName *string

	// BatchSize restricts the number of concurrent builds.
	// Zero indicates no restriction.
	BatchSize int

	// ExtraFlags sends additional command line flags to docker buildx build commands.
	ExtraFlags []string

	// Directory denotes the Docker build directory (defaults behavior assumes the current working directory).
	Directory string

	// DockerfileSource denotes the Dockerfile filename, relative to Directory. Default: Dockerfile.
	DockerfileSource string
}

// NewJob initializes tug and generates a default Job.
func NewJob(debug bool) (*Job, error) {
	platforms, err := AvailablePlatforms(debug)

	if err != nil {
		return nil, err
	}

	cwd, err := os.Getwd()

	if err != nil {
		return nil, err
	}

	return &Job{
		Builder:   TugBuilderName,
		Platforms: DisableNichePlatforms(platforms),
		Directory: cwd,
	}, nil
}

// runBatch executes a batch of platforms.
func (o Job) runBatch() error {
	cmd := exec.Command("docker")
	cmd.Env = os.Environ()

	// Work around spurious buildx warnings
	cmd.Env = append(cmd.Env, "BUILDX_NO_DEFAULT_LOAD=true")

	cmd.Stderr = os.Stderr
	cmd.Stdout = os.Stdout
	cmd.Args = []string{"docker", "buildx"}

	if o.ListImageName != nil {
		cmd.Args = append(cmd.Args, "imagetools", "inspect", *o.ListImageName)
		return cmd.Run()
	}

	cmd.Args = append(cmd.Args, "build", "--builder", TugBuilderName)

	var platformPairs []string

	for _, platform := range o.Platforms {
		platformPairs = append(platformPairs, platform.Format())
	}

	cmd.Args = append(cmd.Args, "--platform")

	if o.LoadPlatform == nil {
		cmd.Args = append(cmd.Args, strings.Join(platformPairs, ","))
	} else {
		cmd.Args = append(cmd.Args, *o.LoadPlatform)
		cmd.Args = append(cmd.Args, "--load")
	}

	if o.Push {
		cmd.Args = append(cmd.Args, "--push")
	}

	cmd.Args = append(cmd.Args, "-t", *o.ImageName)

	if o.DockerfileSource != "" {
		cmd.Args = append(cmd.Args, "-f", o.DockerfileSource)
	}

	cmd.Args = append(cmd.Args, o.ExtraFlags...)
	cmd.Args = append(cmd.Args, o.Directory)

	if o.Debug {
		log.Printf("Command: %v\n", cmd)
	}

	return cmd.Run()
}

// Run schedules builds.
func (o Job) Run() error {
	var platforms []Platform

	for _, platform := range o.Platforms {
		var excludedOs bool

		for _, osExclusion := range o.OsExclusions {
			if platform.Os == osExclusion {
				excludedOs = true
				break
			}
		}

		if excludedOs {
			continue
		}

		var excludedArch bool

		for _, archExclusion := range o.ArchExclusions {
			if platform.Arch == archExclusion {
				excludedArch = true
				break
			}
		}

		if excludedArch {
			continue
		}

		platforms = append(platforms, platform)
	}

	o.Platforms = platforms

	batchSize := o.BatchSize

	if batchSize == 0 {
		return o.runBatch()
	}

	var platformGroups [][]Platform

	for len(o.Platforms) != 0 {
		if len(o.Platforms) < batchSize {
			batchSize = len(o.Platforms)
		}

		platformGroups = append(platformGroups, o.Platforms[0:batchSize])
		o.Platforms = o.Platforms[batchSize:]
	}

	//
	// Work around corruption glitch in buildx --push.
	//
	push := o.Push
	o.Push = false

	for _, platformGroup := range platformGroups {
		o.Platforms = platformGroup

		if err := o.runBatch(); err != nil {
			return err
		}
	}

	if push {
		o.Push = true
		o.Platforms = platforms
		return o.runBatch()
	}

	return nil
}
