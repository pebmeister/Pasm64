;********************************************
;*											*
;*	RENUMBER								*
;*											*
;*	written by Paul Baxter					*
;*											*
;********************************************
				*=	$C000
				TBLLOC	= $A000

				.dsection	install
				.send		install


				;
				;	main entry point
				;
				.dsection	main
				.send		main

				;
				;	init
				;
				.dsection	init
				.send		init

				;
				;	pass1
				;
				.dsection	pass1
				.send		pass1

				;
				;	pass2
				;
				.dsection	pass2
				.send		pass2

				;
				;	utils
				;
				.dsection	utils
				.send		utils

.if debug !=0
				;
				;	debug
				;
				.dsection	debug
				.send		debug
.endif
				;
				;	storage
				;
				.dsection	storage
				.send		storage
