package tug

import (
	"fmt"
	"log"
	"os"
	"os/exec"
)

// RemoveBuildxImageCache deletes any images/layers in the active buildx cache.
func RemoveBuildxImageCache(debug bool) error {
	cmd := exec.Command("docker")
	cmd.Args = []string{"docker", "buildx", "prune", "--force"}
	cmd.Env = os.Environ()
	cmd.Stderr = os.Stderr
	cmd.Stdout = os.Stdout

	if debug {
		log.Printf("Command: %v\n", cmd)
	}

	return cmd.Run()
}

// RemoveTugBuilder deletes the tug buildx builder.
func RemoveTugBuilder(debug bool) error {
	cmd := exec.Command("docker")
	cmd.Args = []string{"docker", "buildx", "rm", TugBuilderName}
	cmd.Env = os.Environ()
	cmd.Stderr = os.Stderr
	cmd.Stdout = os.Stdout

	if debug {
		log.Printf("Command: %v\n", cmd)
	}

	return cmd.Run()
}

// Clean empties the active buildx image cache
// and removes the tug builder,
//
// Returns zero on successful operation. Otherwise, returns non-zero.
func Clean(debug bool) int {
	var status = 0

	if err := RemoveBuildxImageCache(debug); err != nil {
		fmt.Fprintf(os.Stderr, "%v", err)
		status = 1
	}

	if err := RemoveTugBuilder(debug); err != nil {
		fmt.Fprintf(os.Stderr, "%v", err)
		status = 1
	}

	return status
}
