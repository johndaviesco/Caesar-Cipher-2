Caesar-Cipher-2
===============

// Compiling

// Encode

	$ gcc encode.c -o encode

or

	$ gcc encode.c -o encode && [COMMANDS]

// Decode

	$ gcc decode.c -o decode

or 

	$ gcc decode.c -o decode && [COMMANDS]

// Main

	$ cat ptext.txt | ./encode juliuscaeser

		key: JULISCAERTVWXYZBDFGHKMNOPQ - 26
		JWRLS, XSSH PZK JH HES BJFV, UZU


	$ cat ctext.txt | ./decode juliuscaeser
	
		map: GPFQHRSTDAUCVWXYZIEJBKLMNO - 26
		ALICE, MEET YOU AT THE PARK, BOB


// Optional

	$ cat ptext.txt | ./encode juliuscaeser > ctext.txt
	
		key: JULISCAERTVWXYZBDFGHKMNOPQ - 26
		JWRLS, XSSH PZK JH HES BJFV, UZU
	
	$ cat ctext.txt | ./decode juliuscaeser > dtext.txt
	
		map: GPFQHRSTDAUCVWXYZIEJBKLMNO - 26
		ALICE, MEET YOU AT THE PARK, BOB


// checks the difference in files and returns nothing if there is no diferece
// in this case it checks the message against the decrypted message

	$ diff ptext.txt dtext.txt -i

