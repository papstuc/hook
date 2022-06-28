windows hook
--------------
common hook libraries like ms-detours, minhook place a jmp (0xE9 on IA-32) at the beginning of the subroutine, leading to easy detections because the AC can check this with ease.

using this hook does not protect you from integrity checks.

