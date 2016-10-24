// ƒnƒmƒC‚Ì“ƒ	ƒeƒXƒgƒXƒNƒŠƒvƒg
// V‚µ‚­’Ç‰Á‚µ‚½\•¶‚ÌŽg—p•û–@‚ª•ª‚©‚ç‚È‚¢‚Æ¢‚é‚Ì‚Åì‚è‚Ü‚µ‚½B

prontera.gat,160,180,1	script	ƒnƒmƒC‚Ì“ƒˆÄ“àˆõ	112,{
	// ŠÖ”éŒ¾
	function hanoi_init;		// ‰~”Õ‚Ì‰Šú‰»
	function hanoi_move;		// ‰~”Õ‚ÌˆÚ“®
	function hanoi_display;		// ‰~”Õ‚Ì•\Ž¦
	function hanoi_display_sub;
	function hanoi_check;		// ‰~”Õ‚Ìó‘Ô‚ª³‰ð‚©‚Ç‚¤‚©Šm”F
	function hanoi_solve;		// ƒnƒmƒC‚Ì“ƒ‚ð‰ð‚­
	function hanoi_name;		// ”Žš¨–_‚Ì–¼‘O•ÏŠ·

	// ‰~”Õ‚Ì–‡”
	// ‘½‚­‚µ‚·‚¬‚é‚Æ‘å•Ï‚ÈŽ–‚É‚È‚é‚Ì‚Å’ˆÓI
	set @level,4;

	switch(select("ƒnƒmƒC‚Ì“ƒ‚É‚Â‚¢‚Ä","—V‚ñ‚Å‚Ý‚é","‰ð“š‚ðŒ©‚é","‚â‚Á‚Ï‚è‚â‚ß‚é")) {
	case 1:
		// ‰É‚È•û•âŠ®‚¨Šè‚¢‚µ‚Ü‚·B
		mes "[ƒnƒmƒC‚Ì“ƒˆÄ“àˆõ]";
		mes "ƒnƒmƒC‚Ì“ƒ‚Æ‚ÍA" + @level + "–‡‚Ìˆá‚¤‰~”Õ‚ðA";
		mes "•Ê‚ÌêŠ‚ÉˆÚ“®‚³‚¹‚éƒQ[ƒ€‚Å‚·B";
		mes "‰~”Õ‚Ì‘å‚«‚³‚Í”Žš‚Å•\‚³‚ê‚Ä‚¢‚Ü‚·B";
		next;
		mes "[ƒnƒmƒC‚Ì“ƒˆÄ“àˆõ]";
		mes "ƒ‹[ƒ‹‚ÍŽŸ‚Ì‚Q‚Â‚¾‚¯‚Å‚·B";
		mes "Eˆê“x‚É“®‚©‚¹‚é‚Ì‚Íˆê–‡‚¾‚¯";
		mes "E¬‚³‚¢‰~”Õ‚Ìã‚É‘å‚«‚¢‰~”Õ‚Íd‚Ë‚ç‚È‚¢";
		next;
		mes "[ƒnƒmƒC‚Ì“ƒˆÄ“àˆõ]";
		mes "’§í‚ð‚¨‘Ò‚¿‚µ‚Ä‚¢‚Ü‚·B";
		close;
		break;
	case 2:
		// ‰~”Õ‚ð‰Šú‰»‚·‚é
		hanoi_init;
		do {
			mes "[ƒnƒmƒC‚Ì“ƒˆÄ“àˆõ]";
			mes "¡‚Ü‚Å‚É" + @count + "‰ñ‰~”Õ‚ðˆÚ“®‚µ‚Ü‚µ‚½B";
			hanoi_display;
			next;
			set @pos_a , select("‰~”Õ‚`‚©‚ç","‰~”Õ‚a‚©‚ç","‰~”Õ‚b‚©‚ç","‚â‚Á‚Ï‚è‚â‚ß‚é");
			if(@pos_a == 4) { close; end; }
			switch(@pos_a) {
				case 1: set @move_count , @A_count; break;
				case 2: set @move_count , @B_count; break;
				case 3: set @move_count , @C_count; break;
			}
			if(@move_count == 0) {
				mes "[ƒnƒmƒC‚Ì“ƒˆÄ“àˆõ]";
				mes "‚»‚ÌêŠ‚É‰~”Õ‚Í‚ ‚è‚Ü‚¹‚ñB";
				next;
				continue;
			}
			set @pos_b , select("‰~”Õ‚`‚ÖˆÚ“®","‰~”Õ‚a‚ÖˆÚ“®","‰~”Õ‚b‚ÖˆÚ“®","‚â‚Á‚Ï‚è‚â‚ß‚é");
			if(@pos_a == 4) { close; end; }
			if(hanoi_move(@pos_a,@pos_b) == 0) {
				// ˆÚ“®•s‰Â”\
				mes "[ƒnƒmƒC‚Ì“ƒˆÄ“àˆõ]";
				mes "ˆÚ“®‚Å‚«‚Ü‚¹‚ñB";
				next;
				continue;
			}
			set @count,@count + 1;
			if(hanoi_check()) {
				// ³‰ð‚µ‚½Žž‚Ì‚²–J”ü
				mes "[ƒnƒmƒC‚Ì“ƒˆÄ“àˆõ]";
				mes "‚¨Œ©Ž–A³‰ð‚Å‚·B(" + @count + "‰ñ‚Ì‰~”ÕˆÚ“®)";
				mes "Ü‹à‚Æ‚µ‚Ä100Zeny·‚µã‚°‚Ü‚·B";
				set Zeny,Zeny + 100;
				break;
			}
		} while(1);
		close;
		break;
	case 3:
		hanoi_init;
		mes "[ƒnƒmƒC‚Ì“ƒˆÄ“àˆõ]";
		mes "‚Å‚ÍAŽn‚ß‚Ü‚·B";
		hanoi_display;
		next;
		hanoi_solve @level,@A_data,@C_data,@B_data,1,3,2;
		mes "[ƒnƒmƒC‚Ì“ƒˆÄ“àˆõ]";
		mes @count + "‰ñ‚ÌˆÚ“®‚ªÅ’Z‚Å‚·‚ËB";
		close;
	}
	// ŽÀ‰‰
	// hanoi_solve(lv,from_array,to_array,temp_array,from_name,to_name,temp_name)
	function hanoi_solve {
		if(getarg(0) == 1) {
			// hanoi_move ‚Í’l‚ð•Ô‚·ŠÖ”‚È‚Ì‚ÅA’l‚ðŽÌ‚Ä‚é•K—v‚ª‚ ‚é
			set @dummy , hanoi_move(getarg(4),getarg(5));

			// ¡‰ñ‚ÌŽè‡‚ð•\Ž¦
			set @count , @count + 1;
			mes "[ƒnƒmƒC‚Ì“ƒˆÄ“àˆõ]";
			mes "‰ð“š" + @count + " : " + hanoi_name(getarg(4)) + "‚Ì‰~”Õ‚ð" + hanoi_name(getarg(5)) + "‚ÉˆÚ“®";
			hanoi_display;
			next;
		} else {
			hanoi_solve getarg(0) - 1,getarg(1),getarg(3),getarg(2),getarg(4),getarg(6),getarg(5);

			// hanoi_move ‚Í’l‚ð•Ô‚·ŠÖ”‚È‚Ì‚ÅA’l‚ðŽÌ‚Ä‚é•K—v‚ª‚ ‚é
			set @dummy , hanoi_move(getarg(4),getarg(5));

			// ¡‰ñ‚ÌŽè‡‚ð•\Ž¦
			set @count , @count + 1;
			mes "[ƒnƒmƒC‚Ì“ƒˆÄ“àˆõ]";
			mes "‰ð“š" + @count + " : " + hanoi_name(getarg(4)) + "‚Ì‰~”Õ‚ð" + hanoi_name(getarg(5)) + "‚ÉˆÚ“®";
			hanoi_display;
			next;

			hanoi_solve getarg(0) - 1,getarg(3),getarg(2),getarg(1),getarg(6),getarg(5),getarg(4);
		}
	}
	function hanoi_name {
		switch(getarg(0)) {
		case 1: return "A";
		case 2: return "B";
		case 3: return "C";
		}
		return "??";
	}
	// ‰Šú‰»‚·‚é
	function hanoi_init {
		cleararray @A_data,0,@level;
		cleararray @B_data,0,@level;
		cleararray @C_data,0,@level;
		set @A_data[0] , @level + 1;
		set @B_data[0] , @level + 1;
		set @C_data[0] , @level + 1;
		set @A_count , 0;
		set @B_count , 0;
		set @C_count , 0;
		for(set @i,@level ; @i > 0 ; set @i , @i - 1) {
			set @A_data[@A_count + 1] , @i;
			set @A_count , @A_count + 1;
		}
		set @count , 0;
	}
	// “à—e‚ð•\Ž¦‚·‚é
	function hanoi_display {
		mes "A: " + hanoi_display_sub(@A_data,@A_count);
		mes "B: " + hanoi_display_sub(@B_data,@B_count);
		mes "C: " + hanoi_display_sub(@C_data,@C_count);
	}
	function hanoi_display_sub {
		set @__ret$ , "";
		set @__max  , getarg(1);
		for(set @i , 1;@i <= @__max; set @i , @i + 1) {
			// ”z—ñ‚ðƒRƒs[‚·‚éˆ—‚ªd‚·‚¬‚é‚©‚çŽb’èˆ—
			set @__ret$ , @__ret$ + getelementofarray(getarg(0),@i);
		}
		return @__ret$;
	}
	// ‰~”Õ‚ðˆÚ“®‚·‚é
	function hanoi_move {
		set @__pos_a , getarg(0);
		set @__pos_b , getarg(1);
		// ‚Ü‚¸Å‰‚ÉˆÚ“®‚Å‚«‚é‚©ƒ`ƒFƒbƒN
		if(@__pos_a == @__pos_b) {
			// “¯‚¶‰~”Õ‚È‚Ì‚ÅˆÚ“®•s‰Â
			return 0;
		}
		switch(@__pos_a) {
			case 1: set @__move_val_1,@A_data[@A_count]; break;
			case 2: set @__move_val_1,@B_data[@B_count]; break;
			case 3: set @__move_val_1,@C_data[@C_count]; break;
		}
		switch(@__pos_b) {
			case 1: set @__move_val_2,@A_data[@A_count]; break;
			case 2: set @__move_val_2,@B_data[@B_count]; break;
			case 3: set @__move_val_2,@C_data[@C_count]; break;
		}
		if(@__move_val_2 < @__move_val_1) {
			// ˆÚ“®•s‰Â”\i¬‚³‚¢‰~”Õ‚Ìã‚É‘å‚«‚¢‰~”Õ‚ðd‚Ë‚æ‚¤‚Æ‚µ‚½j
			return 0;
		}
		// ŽÀÛ‚ÉˆÚ“®‚³‚¹‚é
		switch(@__pos_a) {
			case 1: set @A_data[@A_count],0; set @A_count,@A_count-1; break;
			case 2: set @B_data[@B_count],0; set @B_count,@B_count-1; break;
			case 3: set @C_data[@C_count],0; set @C_count,@C_count-1; break;
		}
		switch(@__pos_b) {
			case 1: set @A_count,@A_count+1; set @A_data[@A_count],@__move_val_1; break;
			case 2: set @B_count,@B_count+1; set @B_data[@B_count],@__move_val_1; break;
			case 3: set @C_count,@C_count+1; set @C_data[@C_count],@__move_val_1; break;
		}
		// ˆÚ“®‰Â”\
		return 1;
	}
	// Š®¬‚µ‚Ä‚é‚©Šm‚©‚ß‚é
	function hanoi_check {
		for(set @i , 1; @i <= @level; set @i,@i + 1) {
			if(@B_data[@i] != @level - @i + 1) break;
		}
		if(@i == @level + 1) return 1;
		for(set @i , 1; @i <= @level; set @i,@i + 1) {
			if(@C_data[@i] != @level - @i + 1) break;
		}
		if(@i == @level + 1) return 1;
		return 0;
	}
}
