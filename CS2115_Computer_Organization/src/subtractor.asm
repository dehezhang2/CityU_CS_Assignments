; NASM assembler under linux
section .data
  msg1 db "SID stored in the main memory is (SID of Kevin):", 0xa
  len1 equ $ - msg1
  msg2 db "The result after subtraction is:", 0xa
  len2 equ $ - msg2
  msg3 db "EROOR: The result is negative!", 0xa
  len3 equ $ - msg3
  msg4 db "Please input a number less than or equal to 8 digits", 0xa
  len4 equ $ - msg4
  sid db '55199704'
  user db '00000000'
  result db '        '
  hidden db '00000000'
  h db '00000001'
  lb db 0xa
  lblen db $ - lb

section .bss
  num resb 1
  temp resb 1

section .text
  global _start:


_start:
  ; print the sid stored in main memory
  mov eax, 4
  mov ebx, 1
  mov ecx, msg1
  mov edx, len1
  int 0x80
  mov eax, 4
  mov ebx, 1
  mov ecx, sid
  mov edx, 8
  int 0x80
  mov eax, 4
  mov ebx, 1
  mov ecx, lb
  mov edx, 1
  int 0x80

  ; print input prompt
  mov eax, 4
  mov ebx, 1
  mov ecx, msg4
  mov edx, len4
  int 0x80

  ; get user input
  mov eax, 3
  mov ebx, 2
  mov ecx, user
  mov edx, 8
  int 0x80

  ;handle the case when input is less than 8 digits
  mov esi, 7
  mov ecx, 8

  ;store the index of the linebreak in num
find:
  add esi, '0'
  mov [num], esi
  sub esi, '0'
  mov al, [user+esi]
  dec esi
  cmp al, 0xa
  jne find
  cmp esi, 0
  jl sub_start

done:
  mov ecx, 8
  mov esi, 7

  mov al, [num]
  neg al
  add al, '8'

  ; adjust the user input to 000abcd format
adjust_loop:
  mov [temp], al
  cmp esi, [temp]
  jge change_to_earlier
  mov [temp], al  ; store al temporarily into temp
  mov al, [user+esi]  ; al = user[esi]
  mov al, '0'   ; user[esi] = '0'
  mov [user+esi], al
  mov al, [temp]

after_judge:
  dec esi
  loop adjust_loop


  mov esi, 7
  mov ecx, 8

  ; subtract the error back, problem here
s_loop:
    mov al, [user+esi]
    sbb al, [hidden+esi]
    aas
    pushf
    or al, 30h
    popf

    mov [user+esi], al
    dec esi
    loop s_loop

    mov esi, 7
    mov ecx, 8

add_loop:
    mov al, [user+esi]
    adc al, [h+esi]
    aaa
    pushf
    or al, 30h
    popf

    mov [user+esi], al
    dec esi
    loop add_loop



sub_start:
  mov esi, 7
  mov ecx, 8


  ; subtract the numbers bit by bit
sub_loop:
  mov al, [sid+esi]
  sbb al, [user+esi]
  aas
  pushf
  or al, 30h
  popf

  mov [result+esi], al
  dec esi
  loop sub_loop

  jc error_display

  mov eax, 4
  mov ebx, 1
  mov ecx, msg2
  mov edx, len2
  int 0x80

  mov eax, 4
  mov ebx, 1
  mov ecx, result
  mov edx, 8
  int 0x80
  mov eax, 4
  mov ebx, 1
  mov ecx, lb
  mov edx, 1
  int 0x80
  jmp exit_call

  ;display error if carry > 0
error_display:
  mov edx, len3
  mov ecx, msg3
  mov ebx, 1
  mov eax, 4
  int 0x80


exit_call:
  mov eax, 1
  mov ebx, 0
  int 0x80

change_to_earlier:
  mov [temp], al  ; now temp is the index
  sub esi, [temp]     ; now esi is the index of the earlier element
  mov al, [user+esi]  ; al = user[esi]
  add esi, [temp]     ; now esi is the index of the current element
  mov [user+esi], al  ;user[esi] = al
  mov al, [temp]      ;move al back
  jmp after_judge
