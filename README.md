restored_external_hax
=====================

This is basically a fork of [xerub](https://twitter.com/xerub)'s [sshrd](https://github.com/xerub/sshrd). I didn't fork it though just because my version uses a src/ folder, etc. But credit goes to them.

All this does that is different is change the SSH port on the device from 2222 to 22. Oh yeah, it also makes it a lot easier to compile, and does a lot of the work for you.

I got the IOKit headers from [Ryan Petrich](https://twitter.com/rpetrich)'s [iphoneheaders](https://github.com/rpetrich/iphoneheaders). IOUSBDeviceControllerLib.h was taken from iphone-dataprotection stuff.

insert.sh is a tool that will place the new restored_external binary into a ramdisk you have already made using iphone-dataprotection or some other method. This will NOT help you if you just use a normal, non-SSH ramdisk as input. I made this just to make things easier on me, but then I decided to include it because why not?

Booting your new ramdisk is easy: kload a pwnediBSS, send a pwnediBEC, send a DeviceTree, execute said DeviceTree, send your new ramdisk, execute said ramdisk, send a kernel, then boot said kernel.

Questions can be asked by [email](mailto:dayt0n@dayt0n.com), or via [Twitter](https://twitter.com/daytonhasty).

Credits
=======
+[xerub](https://twitter.com/xerub)
+[iphone-dataprotection](https://github.com/dayt0n/iphone-dataprotection)
+[dayt0n](https://twitter.com/daytonhasty)
