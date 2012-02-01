;Piton Game
;Made By Max Gorbanev
;Copyright(C) by Nightmare

.model tiny
.code
.186
org	100h
Start:
       mov ah,09h
       lea dx,msgCopy
       int 21h
       lea dx,msgMade
       int 21h
       lea dx,msgName
       int 21h

	mov ax,CS
	add ax,1000h
	mov ds,ax

	push	0A000h
	pop	es
	mov 	ax,13h
        int 	10h

	mov	di,320*200
	mov	cx,600h

	rep	stosb


	xor	si,si
	mov	bp,10
	jmp	init_food

main_cycle:

	mov	dx,20000
	mov	ah,86h
	int	15h

	mov	ah,1
	int	16h
	jz	short no_keypress
	xor	ah,ah
	int	16h
	cmp	ah,48h
	jne	short not_up
	mov	word ptr cs:move_direction,-320

not_up:
	cmp	ah,50h
	jne	short not_down
	mov	word ptr cs:move_direction,320
not_down:
	cmp	ah,48h
	jne	short not_left
	mov	word ptr cs:move_direction,-1

not_left:
	cmp	ah,4dh
	jne	short no_keypress
	mov	word ptr cs:move_direction,1

no_keypress:
	and	bp,bp
	jnz	short advance_head
	lodsw

	xchg	bx,ax
	mov	byte ptr es:[bx],0
	mov	bx,ax
	inc	bp

advance_head:
	dec	bp
	mov	al,es:[bx]
	and	al,al
	jz	short move_worm
	cmp	al,0Dh
	je	short grow_worm
	mov	ax,3
	int	10h
	retn

move_worm:
	mov	[di],bx
	inc	di
	inc	di
	mov	byte ptr es:[bx],09
	cmp	byte ptr cs:eaten_food,1

	je	if_eaten_food
	jmp	short main_cycle
grow_worm:
	push	bx
	mov	bx,word ptr cs:food_at
	xor	ax,ax
	call	draw_food
	call	random
        and	ax,3fh
	mov	bp,ax

	mov 	byte ptr cs:eaten_food,1

	pop	bx
	jmp	short move_worm

if_eaten_food:
	mov byte ptr cs:eaten_food,0
init_food:
	push	bx
make_food:
	call	random
	and	ax,0fffeh
	mov	bx,ax
	xor	ax,ax
	cmp	word ptr es:[bx+320],ax

	jne	make_food
	mov	word ptr cs:food_at,bx

	mov	ax,0d0dh
	call	draw_food
	pop	bx
	jmp	main_cycle

draw_food:
	mov	es:[bx],ax
	mov	word ptr es:[bx+320],ax
	retn

random:
	mov	ax,word ptr cs:seed
	mov	dx,8e45h
	mul	dx
	inc	ax
	mov	cs:word ptr seed,ax
	retn

eaten_food	db	0
move_direction  dw	1
em  equ 13,10,"$"
msgCopy  db  "Copyright(C) by Nightmare 2000",em
msgMade  db  "Made by Max Gorbanev",em
msgName  db  "*** PITON ***",em
seed:
	food_at	equ	seed+2
	End Start