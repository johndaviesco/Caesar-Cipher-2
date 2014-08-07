Caesar-Cipher-2
===============

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

$ diff –i ptext.txt dtext.txt

