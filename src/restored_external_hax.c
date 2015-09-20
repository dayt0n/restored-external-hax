#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <net/if.h>
#include <assert.h>
#include <CoreFoundation/CoreFoundation.h>
#include "IOKit/IOKitLib.h"
#include "IOKit/IOTypes.h"
#include "IOUSBDeviceControllerLib.h"

IOUSBDeviceDescriptionRef IOUSBDeviceDescriptionCreateWithType(CFAllocatorRef, CFStringRef);

/* reversed from restored_external */
int
init_mux(void)
{
    int i;
    CFNumberRef n;
    CFMutableDictionaryRef dict;
    CFMutableDictionaryRef match;
    IOUSBDeviceDescriptionRef desc;
    IOUSBDeviceControllerRef controller;
    io_service_t service;

    desc = IOUSBDeviceDescriptionCreateWithType(kCFAllocatorDefault, CFSTR("standardMuxOnly"));
    if (!desc) {
        return -1;
    }
    IOUSBDeviceDescriptionSetSerialString(desc, CFSTR("ramdisk tool " __DATE__ " " __TIME__ ));

    controller = 0;
    while (IOUSBDeviceControllerCreate(kCFAllocatorDefault, &controller)) {
        printf("Unable to get USB device controller\n");
        sleep(3);
    }
    IOUSBDeviceControllerSetDescription(controller, desc);

    CFRelease(desc);
    CFRelease(controller);

    dict = CFDictionaryCreateMutable(NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

    i = 7;
    n = CFNumberCreate(NULL, kCFNumberIntType, &i);
    CFDictionarySetValue(dict, CFSTR("DebugLevel"), n);
    CFRelease(n);

    match = IOServiceMatching("AppleUSBDeviceMux");
    for (i = 0; i < 3; i++) {
        CFRetain(match);
        service = IOServiceGetMatchingService(kIOMasterPortDefault, match);
        if (!service) {
            printf("Didn't find, trying again\n");
            sleep(1);
        } else {
            break;
        }
    }
    if (!service) {
        return -1;
    }

    i = IORegistryEntrySetCFProperties(service, dict);
    IOObjectRelease(service);
    CFRelease(dict);

    return i;
}

#include "micro_inetd.c" /* I know, I am a bad person for doing this */
char *execve_params[] = { "/sbin/sshd", "22", "/sbin/sshd", "-i", NULL };

int main(int argc, char* argv[]) {
  printf("Starting  H A K E\n");
  printf("Most of this made by @xerub");
  printf("Edited a bit by @daytonhasty");
    printf("Compiled " __DATE__ " " __TIME__ " using dayt0n's method\n");

    CFMutableDictionaryRef matching;
    io_service_t service = 0;
    matching = IOServiceMatching("IOWatchDogTimer");
    if (matching == NULL) {
        printf("unable to create matching dictionary for class IOWatchDogTimer\n");
    }

    service = IOServiceGetMatchingService(kIOMasterPortDefault, matching);
    if (service == 0) {
        printf("unable to create matching dictionary for class IOWatchDogTimer\n");
    }
    uint32_t zero = 0;
    CFNumberRef n = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &zero);
    IORegistryEntrySetCFProperties(service, n);
    IOObjectRelease(service);

    if (init_mux()) {
        printf("USB init FAIL\n");
    } else {
        printf("USB init succeeded, continuing...\n");
    }

    int i;
    struct stat st;
    for (i = 0; i < 10; i++) {
        printf("Waiting for data partition\n\n");
        if(!stat("/dev/disk0s2s1", &st)) {
            break;
        }
        if(!stat("/dev/disk0s1s2", &st)) {
            break;
        }
        sleep(5);
    }

    printf(" #######  ##    ##\n");
    printf("##     ## ##   ## \n");
    printf("##     ## ##  ##  \n");
    printf("##     ## #####   \n");
    printf("##     ## ##  ##  \n");
    printf("##     ## ##   ## \n");
    printf(" #######  ##    ##\n\n");
    printf("greetz from xerub and dayt0n\n");
    printf("Enjoy your new hax\n");
    printf("You can connect with an SSH tunnel on port 22\n");
    return main2(4, execve_params);
}
