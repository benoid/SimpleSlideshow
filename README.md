# simple-slideshow v2.0 Development Branch

- This branch is rebuild of the original project using better design techniques.  It is not yet functional.

- Note: To run library tests, execute 'make build_tests && make run_tests'

# What's done

* Parse a directory and build a serviceable queue of image and video files
* Refresh directories to check for added files
* Remove files deleted from disk from the queue
* Sorting options for the queue
* Informational slide type which can be configured to be serviced intermittently
* Passing unit tests for everything completed so far.

# To Do
* Qt interface/display
* Configuration subsystem
