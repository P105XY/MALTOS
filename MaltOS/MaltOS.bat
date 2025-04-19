REM Start QEMU Emulator on Window.
REM Start MaltOS 

@Echo off
SET SDL_VIDEODRIVER=windib
SET SDL_AUDIODRIVER=dsound
SET QEMU_AUDIO_DRV=dsound
SET QEMU_AUDIO_LOG_TO_MONITOR=0
qemu-system-x86_64.exe -L . -m 128 -fda MaltOS.ima -soundhw sd16,es1370 -localtime-M pc