.386P
.MODEL  LARGE

SegmentDescriptor  struc
    limit       	dw 		0                   ;Limit low(15:00)    
    offsetLow      	dw 		0                   ;base low (15:0)
    offsetMid      	db 		0                   ;base mid (23:16)
    access      	db 		0                   ;access params
    attributes     	db 		0                   ;limit higher (19:16) + attr
    offsetHigh      db 		0                   ;base high
SegmentDescriptor  ends     
   
   
   
InterruptDescriptor  struc                      
    ioffsetLow     	dw 		0                    ;handler low
    iselector      	dw 		0                    ;handler's selector
    alwaysZero   	db 		0                    ;parameters count, always zero
    access      	db 		0                    ;access level = interrupt gate
    ioffsetHigh     dw 		0                    ;handler high
InterruptDescriptor  ends   
   
   
SpecialIDTPointer  struc     		             ;for lidt
    plimit	       	dw 		0					 ;size
    idtLowPointer   dw 		0                    ;offset low
    idtHighPointer  dw 		0                    ;offset high
SpecialIDTPointer  ends




;ACCESS LEVEL									;76543210 : 7 physical memory
												; 6,5 privilege level
												; 4 = always 1
												; 3 - 1-code; 0-data
												; 2 - ?
												; 1 - 0-read; 1-rw
												; 0 - is referenced

ACCESS_READ        		EQU 00000010B           
ACCESS_CODE        		EQU 10011000B			;code segment access
ACCESS_DATA 			EQU 10010010B			;data segment attr
ACCESS_STACK			EQU 10010010B			;stack segment attr
ACCESS_IDT         	   	EQU 10010010B           ;idt in gdt
INTERRUPT_GATE         	EQU 10001110B			;interrupt gate access level
EXCEPTION_GATE        	EQU 10001111B			;exceptions access level
ACCESS_ALL       		EQU 01100000B           ;any code can use this segment



DATA    segment para use16                 
	DATA_SEGMENT_BEGIN      = 	$

	exit_message            			db 		10, 13, "Success","$"
    protected_greet_message            	db 		"Wait pls until go back to real mode",0
    enter_seconds_message           	db 		"Seconds in protected mode: $"
    interrupt_masks_master          	db  	?            ;master masks
    interrupt_masks_slave          		db  	?            ;slave masks 
    SECOND              				db  	?  
    TIME                				db  	0               
    BUFFER_TIME         				db  	8 		dup(' ')     
										db  	0
    input_time_buffer   				db  	6, 7 	dup(?)  
	
    GDT_BEGIN   = 	$
    GDT 		label   			word                       								;GDT:
    GDT_0       SegmentDescriptor <0, 0, 0, 0, 0, 0>                              
    GDT_GDT     SegmentDescriptor <GDT_SIZE - 1, 0, 0, ACCESS_DATA, 0, 0>             			  
    GDT_CODE_RM SegmentDescriptor <SIZE_CODE_RM - 1, 0, 0, ACCESS_CODE, 0, 0>             	
    GDT_DATA    SegmentDescriptor <DATA_SEGMENT_SIZE-1, 0, 0, ACCESS_DATA + ACCESS_ALL, 0, 0>      
    GDT_STACK   SegmentDescriptor <1000h - 1, 0, 0, ACCESS_DATA, 0, 0>                    
    GDT_TEXT    SegmentDescriptor <2000h - 1,8000h,0Bh, ACCESS_DATA + ACCESS_ALL, 0, 0> 
    GDT_CODE_PM SegmentDescriptor <SIZE_CODE_PM - 1, 0, 0, ACCESS_CODE + ACCESS_READ, 40h, 0>    		
    GDT_IDT     SegmentDescriptor <SIZE_IDT - 1, 0, 0, ACCESS_IDT, 0, 0>                  
    GDT_SIZE    = ($ - GDT_BEGIN)               						
    
	;selectors 
    CODE_RM_DESC 	= 		(GDT_CODE_RM - GDT_0)
    DATA_DESC   	= 		(GDT_DATA - GDT_0)      
    STACK_DESC   	= 		(GDT_STACK - GDT_0)
    TEXT_DESC    	= 		(GDT_TEXT - GDT_0)  
    CODE_PM_DESC 	= 		(GDT_CODE_PM - GDT_0)
    IDT_DESC     	= 		(GDT_IDT - GDT_0)
    
	
    IDTptr    SpecialIDTPointer  <SIZE_IDT, 0, 0>             
    IDT 		label   			word                            			;IDT:
    IDT_BEGIN   = $
	
    irpc    N, 0123456789ABCDEF													;Exceptions descriptors
        IDT_0&N 		InterruptDescriptor <0, CODE_PM_DESC, 0, EXCEPTION_GATE, 0>        
    endm
    
	irpc    N, 0123456789ABCDEF													;More exceptions descriptors		
        IDT_1&N 		InterruptDescriptor <0, CODE_PM_DESC, 0, EXCEPTION_GATE, 0>     ; 10...1F
    endm
	
	IDT_RTC    			InterruptDescriptor <0, CODE_PM_DESC, 0, INTERRUPT_GATE, 0>    
    IDT_KEYBOARD 		InterruptDescriptor <0, CODE_PM_DESC, 0, INTERRUPT_GATE, 0>
	IDT_TIMER			InterruptDescriptor <0, CODE_PM_DESC, 0, INTERRUPT_GATE, 0>
    irpc    N, 0345679ABCDEF
        IDT_2&N         InterruptDescriptor <0, CODE_PM_DESC, 0, INTERRUPT_GATE, 0>  ; 22...2F
    endm	
	
    SIZE_IDT        =       ($ - IDT_BEGIN)
	
              
	DATA_SEGMENT_SIZE   = ($ - DATA_SEGMENT_BEGIN)              
DATA    ends

 
CODE_RM segment para use16

CODE_RM_BEGIN   = $

    assume cs:CODE_RM ,DS:DATA, ES:DATA    
	
START:
    mov 	ax, DATA                         
    mov 	ds, ax                                   
    mov 	es, ax                          
    lea 	dx, enter_seconds_message
    mov 	ah, 9h
    int 	21h
    call 	input_time
    mov 	ds:[TIME], al
	
PREPARE_RTC:    				
    mov 	al, 0Ah
    out 	70h, al                              
    in  	al, 71h                              
    or  	al, 00101111b                        ;set divider for 0.5 sec interrupt
    out 	71h, al                              
	
    mov 	al, 0Bh
    out 	70h, al
    in  	al, 71h
    or  	al, 01010110b                       ;Enable periodic interrupt
    out 	71h, al                       
	
SAVE_MASK:										
    in      al,	21h
    mov     interrupt_masks_master, al			            
    in      al, 0A1h
    mov     interrupt_masks_slave, al		 
    cli
	
LOAD_GDT:                                            
    mov 	ax, DATA			
    mov 	dl, ah								;dl:ax == data
    xor 	dh, dh
    shl 	ax, 4								; ax == data << 4
    shr 	dx, 4								; dx == data << 16 >> 4 = data << 12
    mov 	si, ax
    mov 	di, dx
	
WRITE_GDT:
    lea 	bx, GDT_GDT
   ; mov 	ax, si
   ; mov 	dx, di
    add 	ax, offset GDT
    adc 	dx, 0
    mov 	[bx][SegmentDescriptor.offsetLow], ax
    mov 	[bx][SegmentDescriptor.offsetMid], dl
    mov 	[bx][SegmentDescriptor.offsetHigh], dh
	
WRITE_CODE_RM:                                 
    lea 	bx, GDT_CODE_RM
    mov 	ax,cs
    xor		dh,dh
    mov 	dl,ah
    shl 	ax,4
    shr 	dx,4
    mov 	[bx][SegmentDescriptor.offsetLow], ax
    mov 	[bx][SegmentDescriptor.offsetMid], dl
    mov 	[bx][SegmentDescriptor.offsetHigh],dh
	
WRITE_DATA:                                     
    lea 	bx, GDT_DATA
    mov 	ax, si
    mov 	dx, di
    mov 	[bx][SegmentDescriptor.offsetLow], ax
    mov 	[bx][SegmentDescriptor.offsetMid], dl
    mov 	[bx][SegmentDescriptor.offsetHigh], dh
	
WRITE_STACK:                  
    lea 	bx, GDT_STACK
    mov 	ax, ss
    xor 	dh, dh
    mov 	dl, ah
    shl 	ax, 4
    shr 	dx, 4
    mov 	[bx][SegmentDescriptor.offsetLow], ax
    mov 	[bx][SegmentDescriptor.offsetMid], dl
    mov 	[bx][SegmentDescriptor.offsetHigh], dh
	
WRITE_CODE_PM:  
    lea 	bx, GDT_CODE_PM
    mov 	ax, CODE_PM
    xor 	dh, dh
    mov 	dl,	ah
    shl 	ax, 4
    shr 	dx, 4
    mov 	[bx][SegmentDescriptor.offsetLow],ax
    mov 	[bx][SegmentDescriptor.offsetMid],dl
    mov 	[bx][SegmentDescriptor.offsetHigh],dh    
	
WRITE_IDT:   
    lea 	bx, GDT_IDT
    mov 	ax, si
    mov 	dx, di
    add 	ax, offset IDT
    adc 	dx, 0
    mov 	[bx][SegmentDescriptor.offsetLow], ax
    mov 	[bx][SegmentDescriptor.offsetMid], dl
    mov 	[bx][SegmentDescriptor.offsetHigh], dh        
    mov 	IDTptr.idtLowPointer, ax
    mov 	IDTptr.idtHighPointer, dx
	
FILL_IDT:                                  
    lea eax, TIMER_HANDLER             	
    mov IDT_TIMER.ioffsetLow,ax
    shr eax, 16
    mov IDT_TIMER.ioffsetHigh,ax
	
	lea eax, KEYBOARD_HANDLER             	
    mov IDT_KEYBOARD.ioffsetLow,ax
    shr eax, 16
    mov IDT_KEYBOARD.ioffsetHigh,ax
	
    irpc    N, 34567        				
        lea eax,DUMMY_IRQ_MASTER
        mov IDT_2&N.ioffsetLow, ax
        shr eax,16
        mov IDT_2&N.ioffsetHigh, ax
    endm
	
	lea eax, RTC_HANDLER            		
    mov IDT_RTC.ioffsetLow,ax
    shr eax, 16
    mov IDT_RTC.ioffsetHigh,ax
	
    irpc    N, 9ABCDEF              	
        lea eax,DUMMY_IRQ_SLAVE
        mov IDT_2&N.ioffsetLow,ax
        shr eax,16
        mov IDT_2&N.ioffsetHigh,ax
    endm
	
    lgdt fword ptr GDT_GDT                
    lidt fword ptr IDTptr                  
	
    mov 	eax, cr0                         
    or 		al, 00000001b                      ;allow protected mode
    mov 	cr0, eax                         
	                              
	db  0EAH
	dw  $ + 4								;linear address
	dw  CODE_RM_DESC        
												; jump here
LOAD_SELECTORS:                 
	mov 	ax, DATA_DESC
	mov 	ds, ax                         
	mov 	es, ax                         
	mov 	ax, STACK_DESC
	mov 	ss, ax                         
	xor 	ax, ax
	mov 	fs, ax                              
	mov 	gs, ax                            
		
	lldt 	ax                                ;no ldt used
	
PREPARE_TO_RETURN:
	push 	cs                                
	push 	offset BACK_TO_RM                  
	lea  	edi, ENTER_PM                       
	mov  	eax, CODE_PM_DESC                 
	push 	eax                                
	push 	edi                                    
	
REINITIALIAZE_CONTROLLER_FOR_PM:            
	mov 	al, 00010001b                        
	out 	20h, al                    
	out 	0A0h, al           
	mov 	al, 20h                             
	out 	21h, al                           
	mov 	al, 28h                          
	out 	0A1h, al                            
	mov 	al, 04h                             
    out 	21h, al       
    mov 	al, 02h                             
    out 	0A1h, al      
    mov 	al, 11h                     
    out 	21h, al        
    mov 	al, 01h                             
    out 	0A1h, al       
    mov 	al, 0                              
    out 	21h, al                                 
    out 	0A1h, al         
	
	
	nop
    sti                                  
	
GO_TO_CODE_PM:                       
											; prefix allows to execute retf as 32bit instruction
    db 		66h                                      
    retf
	
BACK_TO_RM:                                
    cli                                    
    in  	al, 70h	                               
	or		al, 10000000b                            
	out		70h, al
	nop
	
REINITIALISE_CONTROLLER:                                      
    mov 	al, 00010001b                            
    out 	20h, al                                  
    out 	0A0h, al                                 
    mov 	al, 8h                                   
    out 	21h, al                                  
    mov 	al, 70h                                 
    out 	0A1h, al     
    mov 	al, 04h      
    out 	21h, al       
    mov 	al, 02h           
    out 	0A1h, al      
    mov 	al, 11h             
    out 	21h, al        
    mov 	al, 01h                   
    out 	0A1h, al
	
PREPARE_SEGMENTS:                            
    mov 	GDT_CODE_RM.limit, 0FFFFh   
    mov 	GDT_DATA.limit, 0FFFFh              
    mov 	GDT_STACK.limit, 0FFFFh            
	
    db  	0EAH                               
    dw  	$ + 4
    dw  	CODE_RM_DESC    
	
    mov 	ax, DATA_DESC    
    mov 	ds, ax                                   
    mov 	es, ax                                   
    mov 	fs, ax                                   
    mov 	gs, ax                                   
    mov 	ax, STACK_DESC
    mov 	ss, ax             
	
ENABLE_REAL_MODE:                       
    mov 	eax, cr0
    and 	al, 11111110b                       
    mov		cr0, eax     
	
    db  	0EAH
    dw  	$ + 4
    dw  	CODE_RM                  	
	
    mov 	ax, STACK_A
    mov 	ss, ax                      
    mov 	ax, DATA
    mov 	ds, ax                      
    mov 	es, ax
    xor 	ax, ax
    mov 	fs, ax
    mov 	gs, ax
    mov 	IDTptr.plimit, 3FFH                
    mov 	dword ptr IDTptr + 2, 0            
    lidt 	fword ptr IDTptr                 
	
REPEAIR_MASK:                              
    mov		al, interrupt_masks_master
    out 	21h, al
    mov 	al, interrupt_masks_slave
    out 	0A1h, al     
	
ENABLE_INTERRUPTS:                      

    nop
    sti                

	
EXIT:                                   
    lea dx, exit_message
    mov ah,9h
    int 21h                        
    mov ax,4C00h   
    int 21H               

input_time proc near                           
    mov 	ah, 0ah							 
    xor 	di, di							   
    mov 	dx, offset ds:[input_time_buffer]		
    int 	21h
    mov 	dl, 0ah								
    mov		ah, 02								
    int 	21h 
    
    mov 	si, offset input_time_buffer + 2		
    cmp 	byte ptr [si], "-"					
    jnz 	II1									
    mov 	di,1 
    inc 	si   
II1:
    xor 	ax, ax						
    mov 	bx, 10						
II2:
    mov 	cl, [si]							
    cmp 	cl, 0dh							
    jz 		input_time_return						
    sub 	cl, '0'							
    mul 	bx     
    add 	ax, cx				
    inc 	si      
    jmp 	II2    
input_time_return:
    ret
input_time endp

SIZE_CODE_RM    = ($ - CODE_RM_BEGIN)      
CODE_RM ends


	
	
;		/////////////////////////////////////////////////////////////////////////
;		/////////////////////////////////////////////////////////////////////////
;		/////////////////////////////////////////////////////////////////////////



CODE_PM  segment para use32
CODE_PM_BEGIN   = $
    assume cs:CODE_PM,ds:DATA,es:DATA      
	
ENTER_PM:                             
	mov edi, 3840                         
    lea esi, protected_greet_message
    call BUFFER_OUTPUT 
	
INFINITE_LOOP:   
	;hlt 									;kills dosbox
    jmp  INFINITE_LOOP     
	
EXIT_PM:                                  
    db 66H								   ;execute as 16bit
    retf                                   
	
EXIT_FROM_INTERRUPT:                       ;like iret but not
    popad
    pop es
    pop ds
    pop eax                               
    pop eax                                  
    pop eax                                
    sti                                    
    db 66H
    retf                                  
	
WORD_TO_DEC proc near                      
    pushad    
    movzx 	eax, ax
    xor 	cx, cx              
    mov 	bx, 10              
LOOP1:                                                 
    xor 	dx, dx              
    div 	bx                 
    add 	dl, '0'             
    push 	dx                
    inc 	cx                 
    test 	ax, ax             
    jnz 	LOOP1          
LOOP2:                                        
    pop 	dx                 
    mov 	[di], dl            
    inc 	di                 
    loop 	LOOP2         
    popad
    ret
WORD_TO_DEC endp



DUMMY_IRQ_MASTER proc near             
    push 	eax
    mov  	al, 20h
    out  	20h, al
    pop  	eax
    iretd
DUMMY_IRQ_MASTER endp


DUMMY_IRQ_SLAVE  proc near   
    push 	eax
    mov  	al, 20h
    out  	20h, al
    out  	0A0h, al
    pop  	eax
    iretd
DUMMY_IRQ_SLAVE  endp

TIMER_HANDLER proc near
	jmp RTC_HANDLER
TIMER_HANDLER endp


RTC_HANDLER proc near      
    push 	ds
    push 	es
    pushad                                
    mov  	ax, DATA_DESC                   
	
SHOW_TIMER:
    mov  	al, 0h                     
    out  	70h, al
    in   	al, 71h                      
    cmp  	al, ds:[SECOND]            
    je   	SKIP_SECOND                  
    mov  	ds:[SECOND], al            
    mov  	al, ds:[TIME] 
    cmp  	ds:[TIME], 0         
    je   	DISABLE_PM         
    xor  	ah, ah
    lea 	edi, ds:[BUFFER_TIME]                   
    call 	WORD_TO_DEC              
    mov  	edi, 3980
    lea  	esi, BUFFER_TIME 
    call 	BUFFER_OUTPUT    
    dec  	ds:[TIME]                
    lea  	esi, BUFFER_TIME
    call 	BUFFER_CLEAR           
    jmp  	SKIP_SECOND               	
	
DISABLE_PM:                   
    mov  	al, 20h
    out  	20h, al
    jmp		EXIT_FROM_INTERRUPT      
	
SKIP_SECOND:                                 
    mov  	al, 20h
    out  	20h, al                               
    popad
    pop 	es
    pop 	ds
    iretd
RTC_HANDLER endp

KEYBOARD_HANDLER proc near                 ;Somewhy keyboard halts back in real mode if in handler isn't in al, 60h
    in   	al, 60h
    push 	eax
    mov  	al, 20h
    out  	20h, al
    pop  	eax
    iretd
KEYBOARD_HANDLER endp


BUFFER_CLEAR  proc near         
    mov 	al, ' '
	push 	ebx
	xor 	ebx, ebx
BUFFER_CLEAR_CYCLE:	
    mov 	byte ptr [esi + ebx], al
    inc 	ebx
	cmp		ebx, 8
	jne		BUFFER_CLEAR_CYCLE
	pop		ebx
    ret
BUFFER_CLEAR  endp

BUFFER_OUTPUT proc near                 
    push 	es
    pushad
    mov  	ax, TEXT_DESC                      
    mov  	es, ax
OUTPUT_LOOP:                               
    lodsb                                       
    or   	al, al
    jz   	OUTPUT_EXIT                      
    stosb
    inc  	edi
    jmp  	OUTPUT_LOOP
OUTPUT_EXIT:                            
    popad
    pop  	es
    ret
BUFFER_OUTPUT ENDP

SIZE_CODE_PM     =       ($ - CODE_PM_BEGIN)
CODE_PM  ENDS



STACK_A segment para stack						;PARA for align
    db  1000h dup(?)
STACK_A  ends
end START