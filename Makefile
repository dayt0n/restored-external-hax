all: restored_external

restored_external:
	@rm -rf tools/;
	@echo Creating tools/ directory…;
	@mkdir tools/;
	@echo Compiling…;
	@xcrun -sdk iphoneos clang --sysroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS8.3.sdk src/restored_external_hax.c -arch armv7 -framework IOKit -framework CoreFoundation -Wall -o tools/restored_external -miphoneos-version-min=6.0;
	@echo Signing with task_for_pid_0 property list…;
	@ldid -Ssrc/tfp0.plist tools/restored_external;
	@echo Built hacked restored_external binary. Can be found in tools/.;
