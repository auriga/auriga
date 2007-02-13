prontera.gat,156,89,6	script	test_chkoption	117,{
	mes "Please enter a value of type!";
	input @value;
	if(checkoption(@value))
		mes "True!";
	else
		mes "False!";
	close;
}
