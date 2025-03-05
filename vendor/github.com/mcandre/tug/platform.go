package tug

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"os/exec"
	"regexp"
	"sort"
	"strings"
)

// TugBuilderName denotes the name of the buildx builder.
const TugBuilderName = "tug"

// TugNodeName denotes the name of the buildx node.
const TugNodeName = "tug0"

// TugBuilderPattern denotes the pattern used to search for the tug builder within the buildx builder list.
var TugBuilderPattern = regexp.MustCompile(`^tug\W+`)

// DefaultPlatformsPattern denotes the pattern used to extract supported buildx platforms.
var DefaultPlatformsPattern = regexp.MustCompile(`Platforms:\W+(?P<platforms>.+)$`)

// PlatformPattern denotes the pattern used to extract operating system and architecture variants from buildx platform strings.
var PlatformPattern = regexp.MustCompile(`(?P<os>[^/]+)/(?P<arch>.+)$`)

// Platform models a targetable Docker image platform.
type Platform struct {
	// Os denotes a buildx operating system, e.g. "linux".
	Os string

	// Arch denotes a buildx architecture, e.g. "arm64".
	Arch string
}

// ParsePlatform extracts metadata from a buildx platform string.
func ParsePlatform(s string) (*Platform, error) {
	match := PlatformPattern.FindStringSubmatch(s)

	if len(match) < 3 {
		return nil, fmt.Errorf("invalid buildx platform: %v", s)
	}

	return &Platform{Os: match[1], Arch: match[2]}, nil
}

// Format renders a buildx platform string.
func (o Platform) Format() string {
	return fmt.Sprintf("%s/%s", o.Os, o.Arch)
}

// Platforms models a slice of platform(s).
type Platforms []Platform

// Len calculates the number of elements in a Platforms collection,
// in service of sorting.
func (o Platforms) Len() int {
	return len(o)
}

// Swap reverse the order of two elements in a Platforms collection,
// in service of sorting.
func (o Platforms) Swap(i, j int) {
	o[i], o[j] = o[j], o[i]
}

// Less returns whether the elements a Platforms collection,
// identified by their indices,
// are in ascending order or not,
// in service of sorting.
func (o Platforms) Less(i int, j int) bool {
	return o[i].Format() < o[j].Format()
}

// EnsureTugBuilder prepares the tug buildx builder.
func EnsureTugBuilder(debug bool) error {
	cmd := exec.Command("docker")
	cmd.Args = []string{"docker", "buildx", "create", "--bootstrap", "--name", TugBuilderName, "--node", TugNodeName}
	cmd.Env = os.Environ()
	cmd.Stderr = os.Stderr

	if debug {
		log.Printf("Command: %v", cmd)
	}

	return cmd.Run()
}

// AvailablePlatforms initializes tug and reports the available buildx platforms.
func AvailablePlatforms(debug bool) ([]Platform, error) {
	if err := EnsureTugBuilder(debug); err != nil {
		return nil, err
	}

	cmd := exec.Command("docker")
	cmd.Args = []string{"docker", "buildx", "inspect", TugBuilderName}
	cmd.Env = os.Environ()
	cmd.Stderr = os.Stderr

	if debug {
		log.Printf("Command: %v", cmd)
	}

	stdoutChild, err := cmd.StdoutPipe()

	if err != nil {
		return []Platform{}, err
	}

	if err2 := cmd.Start(); err2 != nil {
		return []Platform{}, err
	}

	scanner := bufio.NewScanner(stdoutChild)

	var platforms []Platform

	for scanner.Scan() {
		line := scanner.Text()
		match := DefaultPlatformsPattern.FindStringSubmatch(line)

		if len(match) < 2 {
			continue
		}

		platformsText := match[1]
		platformPairsText := strings.Split(platformsText, ", ")

		for _, platformPairText := range platformPairsText {
			platform, err2 := ParsePlatform(platformPairText)

			if err2 != nil {
				return platforms, err
			}

			platforms = append(platforms, *platform)
		}
	}

	if err2 := cmd.Wait(); err2 != nil {
		return platforms, err
	}

	if platforms == nil {
		return platforms, fmt.Errorf("no platforms detected")
	}

	sort.Sort(Platforms(platforms))
	return platforms, nil
}

// NichePlatforms may be disabled by default.
var NichePlatforms = []Platform{
	{
		"linux",
		"mips64",
	},
}

// DisableNichePlatforms filters out some exceedingly niche platforms,
// which may not have associated base image entries on Docker Hub.
func DisableNichePlatforms(platforms []Platform) []Platform {
	var out []Platform

	for _, platform := range platforms {
		var foundNiche bool

		for _, niche := range NichePlatforms {
			if platform == niche {
				foundNiche = true
				break
			}
		}

		if !foundNiche {
			out = append(out, platform)
		}
	}

	return out
}
