global pmmngr_paging_enable
pmmngr_paging_enable:
mov ebx, cr0        ; read current cr0
or  ebx, 0x80000000 ; set PG .  set pages as read-only for both userspace and supervisor, replace 0x80000000 above with 0x80010000, which also sets the WP bit.
mov cr0, ebx        ; update cr0
ret               


global pmmngr_is_paging
pmmngr_is_paging:
mov eax, cr0         ; Move the value of CR0 register to eax
test eax, 0x80000000 ; Test if the PG (Paging) bit is set
jz no_paging         ; Jump to no_paging if the PG bit is not set
; Paging is enabled
mov eax, 1           ; Set eax to 1 (or any other value indicating paging is enabled)
jmp done
no_paging:
; Paging is not enabled
xor eax, eax         ; Set eax to 0 (or any other value indicating paging is not enabled)
done:
ret


global pmmngr_load_PDBR  
pmmngr_load_PDBR:
mov eax, [esp+4]
mov	cr3, eax
ret	


global pmmngr_get_PDBR 
pmmngr_get_PDBR:
mov	eax, cr3
ret


