// Package main implements a CLI application to automate common docker buildx workflows.
package main

import (
	"flag"
	"fmt"
	"os"
	"strings"

	"github.com/mcandre/tug"
)

var flagDebug = flag.Bool("debug", false, "Enable additional logging")
var flagLoad = flag.String("load", "", "Load image of the given platform into local Docker registry as a side effect")
var flagPush = flag.Bool("push", false, "Push all Docker image artifacts to Docker registry as a side effect")
var flagPlatforms = flag.String("platforms", "", "append additional platforms (comma delimited)")
var flagExcludeOS = flag.String("exclude-os", "", "exclude operating system targets (comma delimited)")
var flagExcludeArch = flag.String("exclude-arch", "", "exclude architecture targets (comma delimited)")
var flagGetPlatforms = flag.Bool("get-platforms", false, "Get available buildx platforms")
var flagLs = flag.String("ls", "", "List buildx cache for the given image name, of the form name[:tag]")
var flagT = flag.String("t", "", "Docker image name, of the form name[:tag]")
var flagF = flag.String("f", "", "Dockerfile source filename (default: Dockerfile)")
var flagJobs = flag.Int("jobs", 4, "Number of concurrent build jobs. Zero indicates no restriction.")
var flagExtra = flag.String("extra", "", "Extra flags to send to docker buildx build (comma delimited)")
var flagClean = flag.Bool("clean", false, "Remove junk resources (buildx cache; buildx builder)")
var flagHelp = flag.Bool("help", false, "Show usage information")
var flagVersion = flag.Bool("version", false, "Show version information")

func main() {
	flag.Parse()

	debug := *flagDebug

	switch {
	case *flagClean:
		os.Exit(tug.Clean(debug))
	case *flagHelp:
		flag.PrintDefaults()
		os.Exit(0)
	case *flagVersion:
		fmt.Println(tug.Version)
		os.Exit(0)
	}

	if !*flagGetPlatforms && *flagLs == "" && *flagT == "" {
		fmt.Fprintf(os.Stderr, "missing one or more options; see tug -help")
		os.Exit(1)
	}

	if *flagGetPlatforms {
		platforms, err := tug.AvailablePlatforms(debug)

		if err != nil {
			fmt.Fprintf(os.Stderr, "%v", err)
			os.Exit(1)
		}

		for _, platform := range platforms {
			fmt.Println(platform.Format())
		}

		fmt.Println()

		var nichePlatformStrings []string

		for _, niche := range tug.NichePlatforms {
			nichePlatformStrings = append(nichePlatformStrings, niche.Format())
		}

		fmt.Printf("niche (disabled by default): %v\n", strings.Join(nichePlatformStrings, ","))
		os.Exit(0)
	}

	job, err := tug.NewJob(debug)

	if err != nil {
		panic(err)
	}

	job.Debug = debug

	if *flagPlatforms != "" {
		extraPlatformStrings := strings.Split(*flagPlatforms, ",")

		for _, extraPlatformString := range extraPlatformStrings {
			extraPlatform, err2 := tug.ParsePlatform(extraPlatformString)

			if err2 != nil {
				fmt.Fprintf(os.Stderr, "%v", err2)
				os.Exit(1)
			}

			job.Platforms = append(job.Platforms, *extraPlatform)
		}
	}

	if *flagLoad != "" {
		job.LoadPlatform = flagLoad
	}

	job.ImageName = flagT
	job.BatchSize = *flagJobs
	job.Push = *flagPush
	job.OsExclusions = strings.Split(*flagExcludeOS, ",")
	job.ArchExclusions = strings.Split(*flagExcludeArch, ",")

	if *flagLs != "" {
		job.ListImageName = flagLs
	}

	if *flagT != "" {
		job.ImageName = flagT
	}

	if *flagF != "" {
		job.DockerfileSource = *flagF
	}

	if *flagExtra != "" {
		job.ExtraFlags = strings.Split(*flagExtra, ",")
	}

	args := flag.Args()

	if len(args) > 0 {
		job.Directory = args[0]
	}

	if err2 := job.Run(); err2 != nil {
		fmt.Println(err2)
		os.Exit(1)
	}
}
