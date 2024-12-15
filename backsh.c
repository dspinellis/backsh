/*-
 *
 *  backsh - Backup shell: Copy stdin to the specified output
 *
 *  Copyright 2024 Diomidis Spinellis
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUFFER_SIZE 4096

/*
 * Exit the program after a system call failure with an error message
 * indicating the failure reason.
 */
static void
error_exit(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

int
main(int argc, char *argv[])
{
	if (argc != 3) {
		fprintf(stderr, "Usage: %s directory filename\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	const char *directory = argv[1];
	const char *filename = argv[2];

	// Generate the timestamped file name
	char timestamp[16]; // YYYYMMDDZHHMMSS\0
	time_t now = time(NULL);
	struct tm *tm_info = gmtime(&now); // Use gmtime for UTC (Z)
	strftime(timestamp, size, "%Y%m%dZ%H%M%S", tm_info);

	char filepath[PATH_MAX];
	if (snprintf(filepath, sizeof(filepath), "%s/%s-%s", directory, timestamp, filename) >= sizeof(filepath)) {
		fprintf(stderr, "File path too long\n");
		exit(EXIT_FAILURE);
	}

	// Open the file for writing
	int fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		error_exit("Error opening file");

	// Read from stdin and write to the file
	char buffer[BUFFER_SIZE];
	ssize_t bytes_read;
	while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
		if (write(fd, buffer, bytes_read) != bytes_read)
			error_exit("Error writing to file");

	if (bytes_read == -1)
		error_exit("Error reading from stdin");

	return EXIT_SUCCESS;
}
