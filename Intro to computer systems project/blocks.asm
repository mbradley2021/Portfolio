;Matthew Bradley
;ECE 109-602

; This programs moves a 8x8 box across the screen depending 
; on what the user inputs

; DIRECTIONS to move: 
; w: Moves up, a: Moves left, s: Moves down, d: Moves right

; Change color:
; r: red, g: green, b: blue, y: yellow

; Other commands: 
; return: clears screen, q: quit


		.ORIG x3000
		
		AND R0, R0, #0	;Clear all registers
		AND R1, R1, #0
		AND R2, R2, #0
		AND R3, R3, #0
		AND R4, R4, #0
		AND R5, R5, #0
		AND R6, R6, #0
		AND R7, R7, #0
		
		
		LD R2, START
		LD R6, WHITE
		ADD R5, R5, R2	; Saves starting corner of box
			
		STR R6, R2, #0	;Makes starter block
		ADD R4, R4, #7
LOOP2	ADD R3, R3, #7
LOOP1	ADD R2, R2, #1
		STR R6, R2, #0
		ADD R3, R3, #-1
		BRp LOOP1
		ADD R4, R4 #0
		BRz MOVE
		ADD R2, R2, #-7
		LD R1, DWN1
		ADD R2, R2, R1
		STR R6, R2, #0
		ADD R4, R4, #-1
		BRzp	LOOP2
		
		
		
		
MOVE	AND R0, R0, #0	; Gets users input
		GETC
		
		AND R2, R2, #0	; Check for r for color Red
		LD R2 CRED
		ADD R2, R2, R0
		BRnp NXTGRN
		LD R6  RED
		JSR CHANGECL
		BRnzp MOVE
	
NXTGRN  AND R2, R2, #0	;Check for g for color green
		LD R2 CGREEN
		ADD R2, R2, R0
		BRnp NXTBL
		LD R6 GREEN
		JSR CHANGECL
		BRnzp MOVE
		
NXTBL	AND R2, R2, #0	;Check for b for color blue
		LD R2 CBLUE
		ADD R2, R2, R0
		BRnp NXTYLW
		LD R6 BLUE
		JSR CHANGECL
		BRnzp MOVE
		
NXTYLW	AND R2, R2, #0	;Check for y for color yellow
		LD R2 CYELLOW
		ADD R2, R2, R0
		BRnp NXTWHT
		LD R6 YELLOW
		JSR CHANGECL
		BRnzp MOVE


NXTWHT	AND R2, R2, #0	; Check space bar for color white
		LD R2 CWHITE
		ADD R2, R2, R0
		BRnp NEXTS
		LD R6 WHITE
		JSR CHANGECL
		BRnzp MOVE
	
		
NEXTS	AND R2, R2, #0	;Checks for s to move down
		LD 	R2 DOWNC
		ADD R2, R2, R0
		BRnp NEXTU
		JSR	CLEAR
		JSR	DOWN
		BRnzp MOVE
	
	
NEXTU	AND R2, R2, #0	;Checks w to move down
		LD	R2 UPC
		ADD R2, R2, R0
		BRnp NEXTRT
		JSR CLEAR
		JSR UP
		BRnzp MOVE
			
NEXTRT	AND R2, R2, #0	;Checks d to move right
		LD R2 RIGHTC
		ADD R2, R2, R0
		BRnp NEXTLF
		JSR CLEAR
		JSR RIGHT
		BRnzp MOVE	
	
	
NEXTLF	AND R2, R2, #0	;Checks a to move left
		LD R2 LEFTC
		ADD R2, R2, R0
		BRnp QUIT
		JSR CLEAR
		JSR LEFT
		BRnzp MOVE
	
QUIT	AND R2, R2, #0	;Check q to quit the program
		LD R2 CQUIT
		ADD R2, R2, R0
		BRnp MOVE
		JSR STOP
	
	
	
	
	
		

CLEAR	AND R4, R4, #0	;Clears old box
		AND R3, R3, #0
		AND R2, R2, #0
		AND R1, R1, #0
		
		ADD R2, R2, R5	;Load top left corner of old box
		LD R1 BLACk
		
		STR R1, R2, #0
		ADD R4, R4, #7
LOOPC2	ADD R3, R3, #7
LOOPC	ADD R2, R2, #1
		STR R1, R2, #0
		ADD R3, R3, #-1
		BRp LOOPC
		ADD R4, R4, #0
		BRz BKBCK
		ADD R2, R2, #-7
		LD R0, DWN1
		ADD R2, R2, R0
		STR R1, R2, #0
		ADD R4, R4, #-1
		BRzp LOOPC2
BKBCK	RET
		





DOWN	AND	R4, R4, #0	; Remakes cube 8 lines below
		AND R3, R3, #0
		AND R2, R2, #0
		AND R1, R1, #0
		
		LD R1, DWNUM 	; Move corner down 8 lines 		
		ADD R5, R5, R1
		ADD R2, R2, R5
		
		STR R6, R2, #0
		ADD R4, R4, #7
LOOPD2	ADD R3, R3, #7
LOOPD	ADD R2, R2, #1
		STR R6, R2, #0
		ADD R3, R3, #-1
		BRp LOOPD
		ADD R4, R4, #0
		BRz DWBCK
		ADD R2, R2, #-7
		LD R1, DWN1
		ADD R2, R2, R1
		ADD R1, R2, #0
		STR R6, R2, #0
		ADD R4, R4, #-1
		BRzp LOOPD2
DWBCK	RET	
		
		
		
		
		
UP		AND R4, R4, #0	;Remakes cube 8 lines above
		AND R3, R3, #0
		AND R2, R2, #0
		AND R1, R1, #0
		AND R0, R0, #0
		
		ADD R0, R0, #7
		LD R1, UPNUM	; Move corner up 1 line
LOOPUP	ADD R5, R5, R1
		ADD R0, R0, #-1
		BRzp LOOPUP
		ADD R2, R2, R5
		
		
		STR R6, R2, #0
		ADD R4, R4, #7
LOOPU2	ADD R3, R3, #7
LOOPU	ADD R2, R2, #1
		STR R6, R2, #0
		ADD R3, R3, #-1
		BRp LOOPU
		ADD R4, R4, #0
		BRz UPBCK
		ADD R2, R2, #-7
		LD R1, DWN1
		ADD R2, R2, R1
		ADD R1, R2, #0
		STR R6, R2, #0
		ADD R4, R4, #-1
		BRzp LOOPU2
UPBCK	RET	
		
		
		
		
LEFT	AND R4, R4, #0		; Moves box 8 lines to the left
		AND R3, R3, #0
		AND R2, R2, #0
		AND R1, R1, #0
		
		ADD R1, R1, #-8
		ADD R5, R5, R1
		ADD R2, R2, R5
		
		STR R6, R2, #0
		ADD R4, R4, #7
LOOPL2	ADD R3, R3,	#7
LOOPL	ADD R2, R2, #1
		STR R6, R2, #0
		ADD R3, R3, #-1
		BRp	LOOPL
		ADD R4, R4, #0
		BRz LFBCK
		ADD R2, R2, #-7
		LD R1, DWN1
		ADD R2, R2, R1
		ADD R1, R2, #0
		STR	R6, R2, #0
		ADD R4, R4, #-1
		BRzp LOOPL2
LFBCK	RET		
		
		
		
RIGHT   AND R4, R4, #0		;Moves box 8 lines to the right
		AND R3, R3, #0
		AND R2, R2, #0
		AND R1, R1, #0
		
		ADD R1, R1, #8
		ADD R5, R5, R1
		ADD R2, R2, R5
		
		STR R6, R2, #0
		ADD R4, R4, #7
LOOPR2	ADD R3, R3,	#7
LOOPR	ADD R2, R2, #1
		STR R6, R2, #0
		ADD R3, R3, #-1
		BRp	LOOPR
		ADD R4, R4, #0
		BRz LFBCK
		ADD R2, R2, #-7
		LD R1, DWN1
		ADD R2, R2, R1
		ADD R1, R2, #0
		STR	R6, R2, #0
		ADD R4, R4, #-1
		BRzp LOOPR2
RTBCK	RET	
		
		
		
 
		
		
CHANGECL ADD R2, R2, R5		
		 STR R6, R2, #0	
		 ADD R4, R4, #7
COLOR2	 ADD R3, R3, #7
COLOR	 ADD R2, R2, #1
		 STR R6, R2, #0
		 ADD R3, R3, #-1
		 BRp COLOR
		 ADD R4, R4 #0
		 BRz CLBCK
		 ADD R2, R2, #-7
		 LD R1, DWN1
		 ADD R2, R2, R1
		 STR R6, R2, #0
		 ADD R4, R4, #-1
		 BRzp	COLOR2		
CLBCK	 RET		
		
		
		
		
		
		
		
		
		
		
		
STOP	HALT	
			
			
			
			
			
START	.FILL xDF40

WHITE	.FILL x7FFF
RED		.FILL x7C00
GREEN	.FILL x03E0
BLUE	.FILL x001F
YELLOW	.FILL x7FED
BLACK	.FILL x0000

CQUIT	.FILL -113
CRED	.FILL -114
CGREEN	.FILL -103
CBLUE	.FILL -98
CYELLOW .FILL -121
CWHITE	.FILL -32

DWN1	.FILL 128
UP1		.FILL -128
DWNUM	.FILL 1024
UPNUM	.FILL -128

UPC		.FILL -119
DOWNC	.FILL -115
LEFTC	.FILL -97
RIGHTC	.FILL -100

		.END
