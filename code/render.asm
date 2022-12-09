

    
section .text

%define floats rdi
%define increasingvals rsi
; indices: dw 0,3,6,9,12,15,18,21
SIMD_test:
    VMOVDQU ymm2,[rsi]
    mov dword [rsp-4],0xFFFFFFFF
    VBROADCASTSS ymm1,[rsp-4]
    VPGATHERDD ymm0,[floats + ymm2*4],ymm1
SIMD_done:
    ret






%define inpt xmm0
%define out rax
asm_sin:
    mov dword [rsp-4],__float32__(2.0)
    mov dword [rsp-8],__float32__(4.0)
    mov dword [rsp-12],__float32__(6.0)
    VBROADCASTSS ymm0,[rsp-4]
    VBROADCASTSS ymm1,[rsp-8]
    VBROADCASTSS ymm2,[rsp-12]
    


    VFMADD132PS ymm0,ymm1,ymm2
    ;ymm0 = ymm0 * ymm2 + ymm1
    ;a = a*c+b
    ;a = b*a+c
    ;a = b*c+a


    ret
    ; mov [rbp-8],inpt
    ; fld dword [rbp-8]
    ; fsin
    ; fst dword [rbp-8]
    


;Vect3f*verts;
%define verts rdi
;int numVerts;
%define numVerts rsi
;Vect3f*sin_rot;
%define sin_rot rdx
;Vect3f*cos_rot;
%define cos_rot rcx
%define vertIndex, rax
%define dst r8
%define pos r9

%define sin_rx ymm15
%define sin_ry ymm14
%define sin_rz ymm13
%define cos_rx ymm12
%define cos_ry ymm11
%define cos_rz ymm10
%define x ymm9
%define y ymm8
%define z ymm7
%define temp1 ymm6
%define temp2 ymm5
%define mask ymm4
%define index ymm3
%define temp3 ymm2
%define mask2 ymm1
%define buff ymm0
%define temp4 ymm0
align 32
asm_transformVerts:
    
    ;setup trig
    shr numVerts,3

    VBROADCASTSS sin_rx,[sin_rot]
    VBROADCASTSS sin_ry,[sin_rot+4]
    VBROADCASTSS sin_rz,[sin_rot+8]
    VBROADCASTSS cos_rx,[cos_rot]
    VBROADCASTSS cos_ry,[cos_rot+4]
    VBROADCASTSS cos_rz,[cos_rot+8]
    ;setup mask
    mov dword [rsp-4],0xFFFFFFFF
    VMOVDQU index, [rel indices]
    STMXCSR [rsp-8]
    mov r10d,[rsp-8]
    or r10d,0x8000
    or r10d, 0x0040
    mov [rsp-8],r10d
    LDMXCSR [rsp-8]

align 32
.l1:    


    
    ;setup indices
    ;load posititions
    VBROADCASTSS mask,[rsp-4]
    VBROADCASTSS temp1,dword[pos]
    VPGATHERDD x,[verts + index*4],mask
    VSUBPS x,x,temp1

    VBROADCASTSS mask,[rsp-4]
    VBROADCASTSS temp1,dword[pos+4]
    VPGATHERDD y,[verts +index*4 + 4],mask
    VSUBPS y,y,temp1
    
    VBROADCASTSS mask,[rsp-4]
    VBROADCASTSS temp1,dword[pos+8]
    VPGATHERDD z,[verts+ index*4 + 8],mask
    VSUBPS z,z,temp1
    
    VMULPS temp1,y,cos_rx
    VMULPS temp3,z,sin_rx
    
    VMULPS temp2,y,sin_rx
    
    VMULPS temp4,z,cos_rx
    
    VSUBPS y,temp1,temp3
    VADDPS z,temp2,temp4

    VMULPS temp3,x,sin_ry
    VMULPS temp4,x,cos_ry
    VMULPS temp1,z,cos_ry
    VMULPS temp2,z,sin_ry

    VSUBPS z,temp1,temp3
    VADDPS x,temp2,temp4

    VMULPS temp3,y,sin_rz
    VMULPS temp4,y,cos_rz
    VMULPS temp1,x,cos_rz
    VMULPS temp2,x,sin_rz
   

    VSUBPS x,temp1,temp3
    VADDPS y,temp2,temp4
    

    ;rearrange data order for convienence
    VMOVDQA mask2, [rel indexX]
    VPERMD temp1, mask2, x
    VMOVDQA mask2, [rel indexY]
    VPERMD temp2, mask2, y
    VMOVDQA mask2, [rel indexZ]
    VPERMD temp3, mask2, z
    ;write back
    VMOVDQA mask2, [rel mask036]
    VPMASKMOVD [dst],mask2,temp1
    VPMASKMOVD [dst+32],mask2,temp3
    VPMASKMOVD [dst+64],mask2,temp2
    VMOVDQA mask2, [rel mask147]
    VPMASKMOVD [dst],mask2,temp2
    VPMASKMOVD [dst+32],mask2,temp1
    VPMASKMOVD [dst+64],mask2,temp3
    VMOVDQA mask2, [rel mask25]
    VPMASKMOVD [dst],mask2,temp3
    VPMASKMOVD [dst+32],mask2,temp2
    VPMASKMOVD [dst+64],mask2,temp1

    add dst, 96
    add verts,96

    sub numVerts,1   
    jnz .l1


    ret

    









section .rdata align=64:
    indices: dd 0,3,6,9,12,15,18,21    
    indexX: dd 0,3,6,1,4,7,2,5

    indexY: dd 5,0,3,6,1,4,7,2
    indexZ: dd 2,5,0,3,6,1,4,7

    mask036: dd 0xFFFFFFFF,0,0,0xFFFFFFFF,0,0,0xFFFFFFFF,0
    mask147: dd 0,0xFFFFFFFF,0,0,0xFFFFFFFF,0,0,0xFFFFFFFF

    mask25: dd 0,0,0xFFFFFFFF,0,0,0xFFFFFFFF,0,0

global asm_transformVerts
global asm_sin
global SIMD_test