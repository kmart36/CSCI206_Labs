/*
 * A Linux file examiner
 * CSCI206
 * Katy Martinson
 * Tuesday 1pm
 * Section 61
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {

	if (argc != 2) {
		fprintf(stderr, "Usage: %s FILE\n", argv[0]);
		return 1;
	}

	int f = open(argv[1], O_RDONLY);

	if (f < 0){
		perror("error");
		return 2;
	}

	// use fstat to examine file status
	struct stat buf;
	if (fstat(f, &buf) == -1) {
	  perror("error");
	  return 2;
	}

	printf("st_dev: %ld\n", (long) buf.st_dev);
	printf("st_ino: %ld\n", (long) buf.st_ino);
	printf("st_mode: %lo\n", (unsigned long) buf.st_mode);
	printf("st_nlink: %ld\n", (long) buf.st_nlink);
	printf("st_uid: %ld\n", (long) buf.st_uid);
	printf("st_gid: %ld\n", (long) buf.st_gid);
	printf("st_rdev: %ld\n", (long) buf.st_rdev);
	printf("st_size: %ld\n", (long) buf.st_size);
	printf("st_blksize: %ld\n", (long) buf.st_blksize);
	printf("st_blocks: %ld\n", (long) buf.st_blocks);
	printf("st_atime: %s", ctime(&buf.st_atime));
	printf("st_mtime: %s", ctime(&buf.st_mtime));
	printf("st_ctime: %s", ctime(&buf.st_ctime));

	close (f);
	return 0;
}
