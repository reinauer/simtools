/* PHYUNIX.C v1.0    Physical I/O module for Unix/macOS */

/*
        This is part of ODS2 written by Paul Nankervis,
        email address:  Paulnank@au1.ibm.com

        ODS2 is distributed freely for all members of the
        VMS community to use. However all derived works
        must maintain comments in their source to acknowledge
        the contibution of the original author.
        
        Unix/macOS adaptation for file-based disk images.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "phyio.h"

static int file_handles[256];
static int next_handle = 1;

void phyio_show(void)
{
    printf("Unix/macOS physical I/O module\n");
}

unsigned phyio_init(int devlen, char *devnam, unsigned *handle, struct phyio_info *info)
{
    char filename[256];
    int fd;
    struct stat st;
    
    /* Copy device name to local buffer */
    if (devlen >= sizeof(filename)) {
        return 0; /* Error: name too long */
    }
    
    memcpy(filename, devnam, devlen);
    filename[devlen] = '\0';
    
    /* Open file for reading */
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        return 0; /* Error opening file */
    }
    
    /* Get file size */
    if (fstat(fd, &st) < 0) {
        close(fd);
        return 0; /* Error getting file info */
    }
    
    /* Store file descriptor */
    if (next_handle >= 256) {
        close(fd);
        return 0; /* Too many handles */
    }
    
    file_handles[next_handle] = fd;
    *handle = next_handle++;
    
    /* Fill in device info */
    if (info) {
        info->status = PHYIO_READONLY;
        info->sectors = st.st_size / 512;
        info->sectorsize = 512;
    }
    
    return 1; /* Success */
}

unsigned phyio_read(unsigned handle, unsigned block, unsigned length, char *buffer)
{
    int fd;
    off_t offset;
    ssize_t bytes_read;
    
    if (handle >= 256 || handle < 1) {
        return 0; /* Invalid handle */
    }
    
    fd = file_handles[handle];
    if (fd <= 0) {
        return 0; /* Invalid file descriptor */
    }
    
    /* Calculate byte offset */
    offset = (off_t)block * 512;
    
    /* Seek to position */
    if (lseek(fd, offset, SEEK_SET) != offset) {
        return 0; /* Seek failed */
    }
    
    /* Read data */
    bytes_read = read(fd, buffer, length);
    if (bytes_read != (ssize_t)length) {
        return 0; /* Read failed */
    }
    
    return 1; /* Success */
}

unsigned phyio_write(unsigned handle, unsigned block, unsigned length, char *buffer)
{
    /* Read-only implementation */
    (void)handle;
    (void)block;
    (void)length;
    (void)buffer;
    return 0; /* Write not supported */
}
