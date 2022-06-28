windows hook
--------------
common hook libraries like ms-detours, minhook place a jmp (0xE9 on IA-32) at the beginning of the subroutine, leading to easy detections due to the AC checking it with ease.

directx, opengl and discord functions are most commonly checked.

using this hook does not protect you from integrity checks.
