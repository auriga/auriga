//= Auriga Script ==============================================================
// Ragnarok Online Illusion of Vampire Quest Script	by refis
//= Registry ===================================================================
// IL_VAMP_QUE -> 0�`16
//==============================================================================

gef_dun01.gat,132,223,5	script	�O����#ilgf	110,{
	switch(IL_VAMP_QUE) {
	case 0:
		if(BaseLevel < 170) {
			mes "[�O����]";
			mes "�����͊댯�ł��B";
			mes "�����Ƌ����Ȃ��Ă���";
			mes "���炵�������ǂ����Ǝv���܂��B";
			close;
		}
		mes "[���W��]";
		mes "������Ƃ��������Ă�B";
		mes "���̌�A�����������֍s���āB";
		mes "�A��߂��Ă���΂�����ˁB";
		unittalk getnpcid(0,"���W��#ilgf"),"����ˁH";
		if(!sleep2(500)) end;
		emotion 1,"���W��#ilgf01";
		cloakonnpc "���W��#ilgf";
		cloakoffnpc "���W��#ilgf01";
		unittalk getnpcid(0,"���W��#ilgf01"),"����ˁH";
		if(!sleep2(500)) end;
		emotion 1,"���W��#ilgf02";
		cloakonnpc "���W��#ilgf01";
		cloakoffnpc "���W��#ilgf02";
		unittalk getnpcid(0,"���W��#ilgf02"),"����ˁH";
		if(!sleep2(500)) end;
		emotion 1,"���W��#ilgf03";
		cloakonnpc "���W��#ilgf02";
		cloakoffnpc "���W��#ilgf03";
		unittalk getnpcid(0,"���W��#ilgf03"),"����ˁH";
		if(!sleep2(500)) end;
		emotion 1,"���W��#ilgf03";
		cloakonnpc "���W��#ilgf03";
		cloakoffnpc "���W��#ilgf";
		unittalk getnpcid(0,"���W��#ilgf"),"����ˁH";
//		unittalk getnpcid(0,"���W��#ilgf03"),"����ˁH";
		next;
		mes "[�O����]";
		mes "�����Ƃ��ĂĂ��������I";
		mes "�C���U�邶�Ⴀ��܂��񂩁I";
		mes "������ƌ�����A�ƌ����Ă邯�ǁA";
		mes "���������������ł��傤�B";
		next;
		mes "[���W��]";
		mes "����A�{���ɂ�����ƌ��邾������H";
		mes "������Ƃ����I";
		mes "1���I�@����30�b�I";
		mes "10�b�����ł���������I";
		next;
		mes "[�O����]";
		mes "�_���ł��I";
		mes "�w��{�G�ꂳ���܂��񂩂�ˁI";
		next;
		mes "[���W��]";
		mes "����ȂɎ����M�����Ȃ��́H";
		mes "���܂ł���Ȃ�";
		mes "�x�������Ƃ����������H";
		next;
		mes "[�O����]";
		mes "�����ł��ˁB";
		mes "�قږ����x����Ă��܂����ˁB";
		mes "�l�ԂƂ��Ẵ��W�������";
		mes "�܂��M�����Ă��A";
		mes "���@�g���Ƃ��Ẵ��W�������";
		mes "�M�����܂���I";
		next;
		mes "[���W��]";
		mes "�����c�c�{���ɁA";
		mes "���E�҂̐M������Ȃɔ����Ă�";
		mes "�ʖڂ���H";
		mes "���߂��Ȃ��H";
		mes "�l��D�_��������Ȃ�āI";
		emotion 28,"���W��#ilgf";
		next;
		mes "[�O����]";
		mes "���̐M�S�͎�̂��߂̂��̂ł��B";
		mes "�����Ă��̕��͎���";
		mes "���������Ă��܂��B";
		mes "�u�O������A";
		mes "���W����M���邱�ƂȂ���B�v";
		next;
		mes "[�O����]";
		mes "�������̎��ɚ��������Ă����܂��B";
		next;
		mes "[���W��]";
		mes "���ɂ͕������Ȃ���I";
		next;
		mes "[�O����]";
		mes "������O�ł���B";
		mes "�������������疂�@�g���łȂ�";
		mes "�i�ՂɂȂ��Ă�ł��傤�B";
		emotion 6,"���W��#ilgf";
		next;
		menu "�q�[���A���肢���Ă���낵���ł��傤���H",-;
		emotion 18,"�O����#ilgf";
		mes "[�O����]";
		mes "�������ł��A" +(Sex? "�Z��": "�o��")+ "�B";
		mes "�������K�v�ł����炢�ł��ǂ����B";
		misceffect 313,"";
		next;
		mes "[���W��]";
		mes "���̓񖇐�B";
		mes "���ꂾ���琹�E�҂�";
		mes "�M�����Ȃ��񂾁B";
		next;
		menu "���������Ă����݂����ł����c�c",-;
		mes "[�O����]";
		mes "����Ȃɉ����܂ŕ������܂������H";
		mes "���Ƃ������Ƃ��c�c";
		mes "���M���Ȃ��Ă��܂����悤�ł��B";
		next;
		mes "[���W��]";
		mes "�������I";
		mes "�ǂ����̈ӌ����������̂��A";
		mes "���̖`���җl�ɕ����Ă݂悤��I";
		mes "����Ȃ�����ł���H";
		next;
		mes "[���W��]";
		mes "�ǂ��ł��A�`���җl�H";
		mes "�悩������b��";
		mes "�����Ă͂���܂��񂩁H";
		next;
		if(select("�����܂��傤","�����A��܂��B") == 2) {
			mes "[�O����]";
			mes "�����ł����B";
			mes "�c�O�ł��c�c�B";
			next;
			mes "[�O����]";
			mes "�������������Ȃ�����A";
			mes "���ł����q�˂��������B";
			close;
		}
		mes "[�O����]";
		mes "�ӂ��c�c";
		mes "�킩��܂����B";
		mes "����ł͏��������Ȃ�̂ŁA";
		mes "���ł�����ł���n�߂܂��傤���B";
		setquest 14652;
		set IL_VAMP_QUE,1;
		close;
	case 1:
		mes "[�O����]";
		mes "�`���җl�A";
		mes "���̃Q�t�F���̒n����n��";
		mes "���Ă͓��ʂȗ͂������";
		mes "�Â��ȕ�n�������̂��������ł����H";
		next;
		mes "[�O����]";
		mes "�����X�^�[�����鍡�Ƃ͈Ⴂ�A";
		mes "���̕s�h�Ȕy�����ʂȗ͂�";
		mes "�f�r�������̂�";
		mes "�\�N�Ɉ�x����x���炢��";
		mes "�p�x�ł����B";
		next;
		menu "�Ȃ����͂����Ȃ�܂������H",-;
		emotion 54,"�O����#ilgf";
		mes "[�O����]";
		mes "�`���b";
		next;
		emotion 1,"���W��#ilgf";
		mes "[���W��]";
		mes "�Ȃ�ł�����������̂�H";
		next;
		mes "[�O����]";
		mes "�́A���@�g�����������������̓���";
		mes "���Ă�ꏊ��T���āA";
		mes "�嗤�̂���������T�������ʁA";
		mes "���̐Â��Ȓn����n�̏��";
		mes "���Ă邱�ƂɌ��߂��̂ł��B";
		next;
		mes "[�O����]";
		mes "�����āA��������S�Ă̔ߌ���";
		mes "�n�܂����̂ł��B";
		emotion 7,"���W��#ilgf";
		next;
		mes "[���W��]";
		mes "���A�܂����̘b������[�I";
		next;
		mes "[�O����]";
		mes "�u�т���������������";
		mes "�D��S�͐H�~�ɏ���v";
		mes "�Ȃǂƌ����܂����A";
		mes "���@�g���͉����Ƃ������̂�m�炸�A";
		mes "�����̐l�ɋ�J��������";
		mes "���̂Ȃ�ł��B";
		next;
		mes "[�O����]";
		mes "�Ƃɂ����A���@�g��������";
		mes "�Q�t�F���^���[�����Ă�ƁA";
		mes "�n���̕s�h�Ȏ҂�����";
		mes "�ڂ��s���̂�";
		mes "���R�̂��Ƃ����������m��܂���B";
		next;
		mes "[�O����]";
		mes "�ނ�͎��҂�����";
		mes "���ʂȗ͂ɂ���ē����Ă�̂����āA";
		mes "�l�X�Ȏ������{������ł��B";
		next;
		mes "[���W��]";
		mes "�c�c�^����T�������ƌ����Ă�B";
		next;
		mes "[�O����]";
		mes "�����Ȏ����ŏI����Ă�����";
		mes "�ǂ�������ł��傤���A";
		mes "�₪�Ă��̕s�h�Ȏ҂����̂悤��";
		mes "���̖������̂𓮂������ƁA";
		mes "���͂��g���Ă����鐶���̂�";
		mes "�n��������n�߂܂����B";
		next;
		mes "[�O����]";
		mes "�����Ă��鎞�A";
		mes "���������ꂾ�������ʂȗ͂��A";
		mes "�������Ă��܂��܂����B";
		mes "���̌��ʁA�Â��������n����n��";
		mes "���̂悤�ȉ��������炯��";
		mes "�Ȃ��Ă��܂�����ł��B";
		next;
		mes "[�O����]";
		mes "�l�Ƃ��Ē����Ă͂����Ȃ����C����";
		mes "�����Ă��܂�����ł��I";
		mes "����͐_�ɑ΂���`���ɓ������I";
		next;
		emotion 7,"���W��#ilgf";
		mes "[���W��]";
		mes "���A���@�g���̑O��";
		mes "���������������ˁH";
		mes "���I�Ȋ�������߂Ȃ��ł�������H";
		next;
		mes "[�O����]";
		mes "���̌��t�ɂЂƌ��Ђ̉R�ł�";
		mes "����܂������H";
		next;
		mes "[�O����]";
		mes "�������ł����A�`���җl�H";
		mes "�`���җl�Ȃ�T�d�������邱�ƂɁA";
		mes "�D��S�ő傫�ȍЂ���";
		mes "�����N�����悤�Ȑl������";
		mes "�����𗊂݂܂����H";
		next;
		menu "����͂�����Ɓc�c�댯�ł��ˁB",-;
		mes "[���W��]";
		mes "������Ƒ҂��āI�@�`���җl�I";
		mes "���̘b�������Ă���������B";
		next;
		mes "[���W��]";
		mes "�^����ǋ�����ߒ��ɂ����āA";
		mes "���̕��@����ɐ������Ƃ��A";
		mes "�ǂ����ʂ����������N�����킯�ł�";
		mes "�Ȃ��Ƃ������Ƃ́A";
		mes "������񎄂����͗������Ă��܂��B";
		mes "�����璍�ӂ����Ă��܂��B";
		next;
		mes "[���W��]";
		mes "�m���ɖ��@�g��������";
		mes "���߂������Ƃ͂���܂����A";
		mes "����͂����߂������Ƃł��B";
		mes "���̎����̂������Ŗ��@�Ɠs�s��";
		mes "���W�������Ƃ���������Ȃ��ł����H";
		next;
		mes "[���W��]";
		mes "�A���i�x���c��";
		mes "�V���o���c�o���h�Ƃ����A";
		mes "�����������鍑�𗼘e�ɂ�����";
		mes "���[���~�b�h�K�b�c�������A";
		mes "�ǂ���Ƃ��Γ��ȍ��ɐ��������̂�";
		mes "���@�̂���������Ȃ��ł����B";
		next;
		mes "[�O����]";
		mes "���̂��Ƃ�������x�ӂ݂�Ƃ��Ă��A";
		mes "�y�̒��ň��炬�𓾂�͂��̐l�X��";
		mes "�ꂵ�߂��Ă���̂�";
		mes "�����ł͂���܂��񂩁H";
		next;
		mes "[�O����]";
		mes "�����ċ�����Q�t�F���^���[��";
		mes "���т�F�߂Ă��邩�炱���A";
		mes "����ȏ㕶�匾��Ȃ����Ƃ́A";
		mes "���̂��b�����Ȃ��̂ł��H";
		next;
		mes "[���W��]";
		mes "������ƃO��������H";
		mes "���l�Ɖ�b����";
		mes "���荞�܂Ȃ��ł�������H";
		next;
		mes "[���W��]";
		mes "�D��S�͐���ς��錴���͂ł���A";
		mes "�傫�Ȕ��W�̎�ł��B";
		mes "�Ⴆ�΍������N���s�������Ƃ̂Ȃ�";
		mes "�V���E��q�߂�Ƃ�����A";
		mes "�`���җl�͊댯���Ƃ���������";
		mes "�S�O�����肵�܂����H";
		next;
		menu "�������S�O����Ȃ�A�`���҂ł͂���܂���B",-;
		mes "[���W��]";
		mes "�ł���ˁI";
		mes "���������@�g���͖��m�̗̈��";
		mes "�T������������`���҂Ȃ�ł���I";
		mes "��͂�`���җl�Ȃ�";
		mes "�������Ă��炦��Ǝv���܂����B";
		emotion 33,"���W��#ilgf";
		next;
		mes "[���W��]";
		mes "�O��������A�������H�@�����܂����H";
		mes "�Ƃ������Ƃł��̃m�[�g�������āI";
		next;
		mes "[�O����]";
		mes "����̓_���ł��B";
		mes "�`���җl�����Ƃ̊댯����";
		mes "�킩���Ă��ꂽ�񂶂Ⴀ��܂��񂩁H";
		next;
		mes "[���W��]";
		mes "�T���̕K�v���ɂ��F�߂��ł���I";
		next;
		menu "�����������̂��Ƃł����H",-;
		mes "[�O����]";
		mes "���A���݂��̂��Ƃ����b���āA";
		mes "�̐S�Ȃ��Ƃ��������";
		mes "���܂���ł����ˁB";
		mes "�\���󂠂�܂���B";
		next;
		mes "[�O����]";
		mes "��烋�[���~�b�h�K�b�c�̋���ł́A";
		mes "���̕s�h�Ȏ҂����̐���";
		mes "�����߂��Ȃ��悤�ɁA";
		mes "����I�Ɏi�Ւc�𑗂���";
		mes "�ގ������Ă���܂����B";
		next;
		mes "[�O����]";
		mes "���������ގ��ɗ����̂ł����A";
		mes "�����ł����^0000cd�m�[�g^000000���E������ł��B";
		next;
		menu "�m�[�g�ł����H",-;
		mes "[�O����]";
		mes "�͂��B�Q�t�F���^���[�̖��@�g����";
		mes "���Ƃ������̂��Ǝv���A";
		mes "�m�F�̂��߃m�[�g��������";
		mes "^0000cd�{�~^000000�Ƃ������O��������Ă܂����B";
		mes "����������̖��ł��傤�B";
		next;
		mes "[���W��]";
		mes "�������A�������͂���Ȗ��O�A";
		mes "�L���ɂ���܂���B";
		mes "���e��ǂ�ł݂�ƁA";
		mes "�M���h�����Ȃ̂͊ԈႢ�Ȃ��ł����B";
		mes "^0000cd����^000000�͂���Ȑl�͂��܂���B";
		next;
		menu "���݁H",-;
		emotion 33,"���W��#ilgf";
		mes "[���W��]";
		mes "�`���җl�A�����s���ł��ˁB";
		mes "�M���h�ɖ₢���킹�Ă݂���A";
		mes "�y���̂ɂ����炵���ł��B";
		mes "�{�~�Ƃ����l��������ˑR�A";
		mes "�s��������܂����悤�ł��ˁB";
		next;
		menu "���̂��ꂪ�������ɁH",-;
		mes "[���W��]";
		mes "���������ŏ��͂��ꂪ";
		mes "�C�ɂȂ�����ł����A";
		mes "�m�[�g�𒲂ׂ���";
		mes "�u���́H�v�Ƃ������";
		mes "�u�ǂ�����āH�v�Ƃ����^�₪";
		mes "������ł��܂����B";
		next;
		mes "[�O����]";
		mes "���e�����e�ł����A";
		mes "������[���Ȃ̂́c�c";
		mes "���Ⓖ�ڂ����ɂȂ��Ă��������B";
		mes "������^0000cd�Ō�̃y�[�W^000000�܂ł�";
		mes "�߂���Ȃ��悤�ɒ��ӂ��Ă��������B";
		next;
		mes "[���W��]";
		mes "����[�I";
		mes "���ɂ͌����Ă���Ȃ������ɁI";
		mes "���ʂ��[�I";
		mes "���ꂪ���E�҂̂�邱�Ƃ��[�I";
		next;
		mes "[�O����]";
		mes "���W������̂��Ƃ͋C�ɂ����A";
		mes "�����ɂȂ��Ă��������B";
		chgquest 14652,14653;
		set IL_VAMP_QUE,2;
		close;
	case 2:
		mes "�]�O�����i�Ղ̎������{��";
		mes "�@����悹��ƁA";
		mes "�@�y����������݂�����";
		mes "�@���肪�h�炮�悤�ȋC�������B";
		mes "�@�p�S�[���y�[�W���߂����Ă݂��]";
		next;
		mes "[����������]";
		mes "�V�����������擾����ߒ��ŁA";
		mes "�ς��؂ꂸ�܂��|��Ă��܂����B";
		mes "���Ȃ��̗́A���Ȃ��}�i��";
		mes "��ɑ�����������B";
		next;
		mes "[����������]";
		mes "�\�t�B�A���}�i�|�[�V������";
		mes "���ނ̂������B";
		mes "���܂Ŏア���̂𖂖@�̗͂�";
		mes "�������悤�ƍl���Ă�����";
		mes "����͍őP�ł͂Ȃ��������B";
		next;
		mes "���ʂ̖�ł͂Ȃ��A����Ȗ�Ȃ�΁H";
		mes "���@�ł͂Ȃ��̎������P������";
		mes "���������Ȃ��̂ł͂Ȃ����H";
		next;
		mes "[����������]";
		mes "��ɓ���|�[�V������";
		mes "�ア���̂�₤���̂ł͂Ȃ��A";
		mes "���ʂ̓��̂���Ղɂ���";
		mes "�����܂΂���ŁA";
		mes "�ǂ�����Ɍ����ĂȂ������B";
		next;
		mes "�����ǁA���ɓK�����ؗ͂Ɩ��͂�";
		mes "�����܂݂����ȕ����A";
		mes "�����̎�ō���̂ł�";
		mes "�Ȃ����낤���H";
		next;
		mes "[����������]";
		mes "�}���قŃQ�t�F���^���[�̗��j��";
		mes "�ǂ�ŁA�n�����Ɋւ��Ēm�����B";
		mes "�ǂ�����Ď��҂�����";
		mes "�����Ă�񂾂낤�H";
		mes "���̐����͂͂��������Ȃ񂾂낤�H";
		next;
		mes "���ɍs���ɂ͋����K�v���c�c�B";
		mes "�Ƃɂ��������A���ɍs���Ă݂悤�B";
		next;
		mes "[����������]";
		mes "���l�Ɍ������B";
		mes "�c�O�Ȃ���c�c�������Ă�";
		mes "�V���Ȕ����͖��������B";
		next;
		mes "�O�ɉ����������̂��A";
		mes "�����̍��Ղ����������Ɏc����Ă�B";
		mes "�����M���h���̎d�Ƃ���B";
		mes "�����͂₯�ɔ�ꂽ�B�����Q�Ȃ���B";
		next;
		mes "[����������]";
		mes "�����啂����͐H�ו����Ȃ�����";
		mes "�]���r�����̌����z���Ă���B";
		mes "�����č��������̌����z������";
		mes "�P���Ă���B";
		next;
		mes "�啂���������̂ɋ�J�����B";
		mes "�����̋߂�����Ȃ�������";
		mes "����ł������B";
		mes "��ꂽ�B";
		next;
		mes "[����������]";
		mes "�{���͕�ꂩ���ȉ������������B";
		mes "�]���r���啂��݂�ȁA";
		mes "�s�v�c�ȂقǑ�l�����B";
		mes "�����������̂��킩��Ȃ����A";
		mes "�����X�^�[����l��������_���āA";
		mes "�����͂��[�������Ă݂悤�B";
		next;
		mes "�]�ǂ߂�̂͂��̕ӂ܂ł������B";
		mes "�@�m�[�g�����𗣂��ƁA";
		mes "�@�O�����i�Ղ��m�[�g������]";
		chgquest 14653,14654;
		set IL_VAMP_QUE,3;
		close;
	case 3:
		mes "[�O����]";
		mes "�����^0000cd���L�������m�[�g^000000�ł��B";
		mes "�Ƃ��閂�@�g�����A�s�h�Ȏ҂�����";
		mes "����Ȑ����͂𗘗p����";
		mes "^0000cd�ؗ͂Ɩ��͂����������";
		mes "�Ɋւ��錤��^000000���������e��";
		mes "������Ă���܂��B";
		next;
		menu "���������[���ł��ˁB",-;
		emotion 33,"���W��#ilgf";
		mes "[���W��]";
		mes "�����ł��B";
		mes "����͖��p�t�M���h�̕���";
		mes "�������ׂ����̂ł���B";
		mes "�����̋L�^�͍�����";
		mes "�w�ǔp������Ă��܂�����ˁB";
		next;
		mes "[�O����]";
		mes "�������̃m�[�g��";
		mes "���ꂾ���ł͂���܂���B";
		mes "�{�ɐG�ꂽ���A^0000cd��ȋC�z^000000��";
		mes "�����܂���ł������H";
		next;
		mes "[�O����]";
		mes "���̃m�[�g���狭���v�O��";
		mes "�������܂��B";
		mes "�m�[�g�̎����傪�c���������v�O�ŁA";
		mes "�m�[�g����ɓ��ꂽ�҂�";
		mes "^0000cd���Ɉ������荞�����Ƃ��Ă��܂��B^000000";
		next;
		mes "[���W��]";
		mes "�u�Ȃ��H�v�Ƃ����^����";
		mes "�u�ǂ�����āH�v�̕���";
		mes "�C�ɂȂ�܂���ˁH";
		mes "���ꂪ�ǂ�����ĉ\�Ȃ̂��A";
		mes "�Ȃ����X���������̂��A";
		mes "�m�肽������܂��񂩁H";
		next;
		mes "[���W��]";
		mes "�����炿����Ƒ݂��Ă�I";
		mes "�}�W�ł�����Ɠǂނ���������B";
		mes "�����𖾂��Ă݂���񂾂���I";
		next;
		mes "[�O����]";
		mes "���@�g���͂����Ƃ��Ă��Ȃ����I";
		mes "���̃m�[�g�͎�ɂ������̂�";
		mes "�ǂ����ֈ��������Ă����܂��B";
		mes "�m�[�g�̍Ō�̃y�[�W���J����";
		mes "���̂ǂ����֍s���邱�Ƃ�";
		mes "�𖾂��ꂽ��ł��B";
		next;
		mes "[���W��]";
		mes "���͂▼�O����Ă�ł���Ȃ��I";
		next;
		mes "[�O����]";
		mes "���O�ɒ��ׂĂ݂�ƁA";
		mes "�׈��ȋC�z�͂���܂���ł����B";
		mes "�����Ȕ߂��݁A�l��A���]�c�c";
		next;
		mes "[�O����]";
		mes "�������̃m�[�g�̎������";
		mes "�m�[�g����ɓ��ꂽ�҂�";
		mes "^0000cd�`���������t�����邩�A";
		mes "�������]������^000000�������̂ł�";
		mes "�Ȃ��ł��傤���B";
		next;
		mes "[�O����]";
		mes "���Ɏi�Ւc�Ɩ��@�g����";
		mes "�����Ɍ��������֍s���܂����B";
		mes "���ꂩ�炾���Ԏ��Ԃ��o���Ă���̂�";
		mes "�����ɖ߂��Ă��܂���B";
		next;
		menu "�ł́A�����s���Ă݂܂��傤���H",-;
		mes "[�O����]";
		mes "�`���җl���H";
		mes "�ӂށc�c";
		mes "�m���ɂ��̖��@�g������";
		mes "����ɂȂ�Ǝv���܂����A";
		mes "���v�ł����H";
		next;
		menu "�A��߂��Ηǂ��ł����H",-;
		mes "[�O����]";
		mes "�����܂ł͕K�v����܂���B";
		mes "�`���җl��^0000cd�ނ��������^000000";
		mes "�������m�F���A";
		mes "�������K�v�Ȃ珕�����A";
		mes "�`��������΂���������A����";
		mes "��������Ό��\�ł��B";
		next;
		mes "[���W��]";
		mes "�͂��I�@�͂�!!";
		mes "�����I�@����!!";
		next;
		mes "[�O����]";
		mes "�����s�����炢���̂ł����A";
		mes "���������`�������邾���łȂ��c�c";
		mes "�`���b";
		next;
		mes "[���W��]";
		mes "�Ȃ�ł܂���������̂�I";
		next;
		mes "[�O����]";
		mes "�c�����l���M�p�ł��Ȃ��̂ɁA";
		mes "�������̃m�[�g��";
		mes "���Ȃ���΂Ȃ�܂���B";
		mes "�������������������ɂ���l��";
		mes "�߂�Ȃ��Ȃ鋰�ꂪ����܂��B";
		next;
		mes "[���W��]";
		mes "�Ȃ�A�����ꏏ�ɁI";
		next;
		mes "[�O����]";
		mes "���W������͂����Ŏ���";
		mes "�ҋ@���܂��傤�B";
		mes "�m�[�g�ɐG��悤��";
		mes "�v��Ȃ��ł��������ˁB";
		next;
		emotion 28,"���W��#ilgf";
		mes "[���W��]";
		mes "���ŁH";
		mes "�����i�՗l�ɉ������������H";
		next;
		mes "[�O����]";
		mes "�W���W�����񂩂烂�W������";
		mes "�m�[�g�ɐG�ꂳ���Ȃ��悤�ɂ�";
		mes "�\���n����܂����B";
		mes "�Y��܂������H";
		next;
		mes "[���W��]";
		mes "�m���I";
		mes "�v���o���Ȃ��I";
		mes "�V�X�^�[�E�W�F�����߂�����A";
		mes "�O�������񂪎��ɂ������Ƃ�";
		mes "�S���������Ă�邩��ˁI";
		next;
		mes "[�O����]";
		mes "�ł͖`���җl�A�������ł�����";
		mes "���ł����������Ă��������B";
		chgquest 14654,14655;
		set IL_VAMP_QUE,4;
		close;
	default:
		mes "[�O����]";
		mes "�����͗ǂ��ł����H";
		mes "�m�[�g�̌���������";
		mes "�s���܂����H";
		next;
		if(select("�͂��B�����Ă�������","������") == 2) {
			mes "[�O����]";
			mes "�킩��܂����B";
			mes "�������ς܂�����A";
			mes "���ł����������Ă��������B";
			close;
		}
		mes "[�O����]";
		mes "�ł́A�m�[�g���J���܂��B";
		next;
		mes "�]�m�[�g�Ɏ���悹��ƁA";
		mes "�@�O�����i�Ղ��Ō�̃y�[�W��";
		mes "�@�߂������B";
		mes "�@�ڂ̑O�������ɂȂ�A";
		mes "�@�ǂ����֋z�����܂��C�������]";
		if(IL_VAMP_QUE == 4) {
			chgquest 14655,14656;
			set IL_VAMP_QUE,5;
		}
		close2;
		warp "gef_d01_i.gat", 114, 216;
		end;
	case 15:
		mes "[�O����]";
		mes "���̘b�𕷂��Ă��������B";
		mes "���ꂩ�A�^���[�ɂ��߂肭�������B";
		next;
		emotion 39,"���W��#ilgf";
		mes "[���W��]";
		mes "���[��[�I";
		next;
		menu "�܂����������Ă܂����H",-;
		mes "[���W��]";
		mes "���I";
		mes "����ƋA���Ă����I";
		mes "�������͂ǂ��ł����H";
		next;
		mes "[�O����]";
		mes "�`���җl�A�������łȂɂ��ł��B";
		mes "�݂Ȃ���͖����ł������H";
		next;
		mes "�]�O�����i�Ղƃ��W�������";
		mes "�@�m�[�g�̌��������̘b�������B";
		mes "�@��s�͊Ď��̂��ߎc���Ă���Ƃ�";
		mes "�@�`����`�����]";
		next;
		emotion 52,"���W��#ilgf";
		mes "[���W��]";
		mes "����[�A�������[�I";
		mes "�����Ɠ����悤��";
		mes "�S�R�Ⴄ���E�Ƃ��I";
		next;
		mes "[���W��]";
		mes "����Ȃ̏��߂ĕ������I";
		mes "�ǂ�Ȍ�������H";
		mes "����ς��̃m�[�g��";
		mes "�����̓���������̂��ȁH";
		next;
		mes "[���W��]";
		mes "�������l�Ԃ𗝉�����";
		mes "���@���p�C�A�I";
		mes "��������́c�c�I";
		next;
		mes "[���W��]";
		mes "���������Ⴂ���Ȃ��I";
		mes "�O��������I";
		mes "�Ȃ�Ƃ��Ă��s���Ȃ���I";
		mes "�s�����Ă��������I�@���肢���܂��I";
		next;
		mes "[�O����]";
		mes "�������낤�Ƃ��j�~���܂��B";
		mes "��𗣂��Ă��������B";
		next;
		mes "[���W��]";
		mes "�����A�����A�ق�ƁI";
		mes "�����߂���񂾂���I";
		next;
		mes "[�O����]";
		mes "�`���җl�A";
		mes "����Ȃ��ꏊ�ŋ�J�����ł��傤�B";
		mes "�������Ԃ��������̂Ȃ�A";
		mes "���܂Ɍ��������ɂ���l�B��";
		mes "�󋵂�`���Ă�������΍K���ł��B";
		next;
		mes "[���W��]";
		mes "����Ȃ��Ƃ͎��ɂ��C������I";
		mes "���A�o����q�Ȃ�ł��I";
		next;
		mes "[�O����]";
		mes "���W������͖ق��Ă�����Ⴂ�B";
		next;
		mes "[�O����]";
		mes "�`���җl�A";
		mes "�{���ɂ��肪�Ƃ��������܂����B";
		mes "���ꂩ���";
		mes "^0000cd�m�[�g�̌��������ɍs�����́A^000000";
		mes "���ɐ��������Ă��������B";
		chgquest 14666,202090;
		set IL_VAMP_QUE,16;
		getexp 300000000,0,1;
		getexp 0,60000000,0;
		getitem 25271,10;
		close;
	case 16:
		mes "[�O����]";
		mes "�`���җl�A";
		mes "�m�[�g�̌��������֍s���܂����H";
		next;
		if(select("�͂�","������") == 2) {
			mes "[�O����]";
			mes "�킩��܂����B";
			mes "�K�v�ɂȂ�����";
			mes "�܂����炵�Ă��������B";
			close;
		}
		mes "[�O����]";
		mes "�ł́A";
		mes "��������낵�����肢�������܂��B";
		close2;
		warp "gef_d01_j.gat", 114, 216;
		end;
	}
}

gef_dun01.gat,134,224,1	script	���W��#ilgf	123,{
	if(IL_VAMP_QUE == 0) {
		mes "[���W��]";
		mes "�`���җl�������p�ł����H";
		mes "��������ƖZ�����āc�c";
		mes "�����p��������Ȃ�";
		mes "�����̎i�Ղɘb���Ă��������B";
		close;
	}
	else if(IL_VAMP_QUE < 4) {
		mes "[���W��]";
		mes "�m�[�g�A�m�[�g�ǂ݂����c�c";
		mes "�m�[�g�c�c�B";
		close;
	}
	else if(IL_VAMP_QUE < 16) {
		mes "[���W��]";
		mes "�m�[�g�A�m�[�g�ǂ݂����c�c";
		mes "�m�[�g�c�c�B";
		mes "�m�[�g�̌��������ɍs���̂ł�����A";
		mes "�O�����i�Ղɘb�������Ă��������B";
		mes "�����A��Ă����ė~�����c�c�B";
		close;
	}
	mes "[���W��]";
	mes "�����`�m�[�g�A";
	mes "���ł��ǂ߂��炢���̂ɂȁ`�B";
	next;
	mes "[�O����]";
	mes "���ɂ��v��Ȃ����Ƃł��B";
	next;
	mes "[���W��]";
	mes "�m�[�g�I�@�m�[�g�I";
	close;
}

gef_dun01.gat,133,221,1	script	���W��#ilgf01	123,{
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_dun01.gat,130,222,5	script	���W��#ilgf02	123,{
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_dun01.gat,130,224,5	script	���W��#ilgf03	123,{
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,113,230,5	script	�W�F��#ilgf01	79,{
	switch(IL_VAMP_QUE) {
	case 5:
		mes "[�W�F��]";
		mes "�A���g���[�k����͂����Ɏc���āA";
		mes "���ƃ}���i���񂪍s���܂��B";
		mes "�ًc����܂����H";
		next;
		mes "[�}���i]";
		mes "�퓬���̎���";
		mes "�A���g���[�k����ōs���܂��B";
		mes "�V�X�^�[�W�F���͎c���Ă��������B";
		mes "���̕������������ł����B";
		next;
		mes "[�A���g���[�k]";
		mes "�}���i���񂪎c��A";
		mes "�l�ƃV�X�^�[�W�F���̓�l�̕���";
		mes "�����񂶂�Ȃ��ł����H";
		mes "�X�̔\�͂�����ƁA";
		mes "�����炪�o�����X����ꂻ���ł��B";
		next;
		mes "[�W�F��]";
		mes "����͂����܂���B";
		mes "�����͕s�h�Ȏ҂����ň�t�ł��B";
		mes "���E�ғ�l�ŒT��������";
		mes "���Ղ��ł��B";
		next;
		mes "[�A���g���[�k]";
		mes "���@�g���Ƃ��Ă�";
		mes "���������܂���ˁI";
		mes "�l���]���r����ɏ�肭�킦�܂���I";
		next;
		mes "[�}���i]";
		mes "�ނ����l���c��A";
		mes "��l���T��������ǂ��ł��H";
		next;
		mes "[�W�F��]";
		mes "����͂����܂���B";
		mes "��l�̕����������̎��Ԃ�";
		mes "�Ή��ł��܂�����B";
		next;
		mes "[�A���g���[�k]";
		mes "���������Ɉ�l�Ŏc��������";
		mes "�������N������ǂ����܂����H";
		next;
		menu "���́c�c�O�����i�Ղ̎g���ł����B",-;
		mes "[�}���i]";
		mes "��H�@�����l�H";
		next;
		menu "������������ł����H",-;
		mes "[�}���i]";
		mes "�l��T���Ȃ��Ă͂Ȃ�܂���B";
		next;
		mes "[�A���g���[�k]";
		mes "���_���������Ăǂ������ł����I";
		mes "�`���җl�A�������ǂ��������Ȃ̂�";
		mes "�����͕����܂������H";
		mes "���Ƃ��}���̂ŁA";
		mes "�����܂�Ő������܂��B";
		next;
		mes "[�A���g���[�k]";
		mes "�����͌����̃Q�t�F���̒n����n��";
		mes "�w�Ǔ����ꏊ�ł��B";
		mes "�����A�m�[�g�̎������";
		mes "�L�������p�Ȃ̂ł��傤�B";
		next;
		mes "[�A���g���[�k]";
		mes "�l�����͂������ǂ�ȗ͂ŁA";
		mes "���̖ړI�ō��ꂽ�̂���";
		mes "�������ɗ��܂����B";
		next;
		mes "[�A���g���[�k]";
		mes "�ڂɗ��܂���̂����ɂȂ��A";
		mes "������؂�グ�悤�Ƃ������A";
		mes "�ꏏ�ɗ��Ă���^0000cd�i�ՂƖ��@�g��^000000��";
		mes "���Ȃ����ƂɋC�Â��܂����B";
		next;
		mes "[�A���g���[�k]";
		mes "�ӂ��T���܂������A";
		mes "�m�[�g�̎�����̉ߋ��̋L����";
		mes "���݂����󋵂Łc�c";
		mes "�������̖��@�g���̌���";
		mes "���������Ɍ��ꂽ��";
		mes "�������肵�Ă��܂��B";
		next;
		mes "[�A���g���[�k]";
		mes "���肪�Ȃ��̂�";
		mes "�����킯�ĒT�����ƌ��߂āA";
		mes "�ӌ������킵�Ă���";
		mes "�Ƃ���ł��āc�c�B";
		next;
		mes "[�A���g���[�k]";
		mes "�c�c����ȂƂ���ɖ`���җl��";
		mes "���炵�Ă���āA�{���ɏ�����܂��B";
		mes "�N���c��A�N���T���ɍs���̂�";
		mes "�b���Ă����̂ł����A";
		mes "�l�l�ɂȂ����̂�^0000cd��l���ɕ������^000000";
		mes "�T���ɍs���Ηǂ��ł��傤�B";
		next;
		menu "�������l�B�̓����́H",-;
		mes "[�W�F��]";
		mes "�������i�Ղ̖���^0000cd�W���r���[^000000�ŁA";
		mes "���@�g���̖���^0000cd�W���W��^000000�ł��B";
		mes "�T�^�I�Ȑ��E�҂Ɩ��@�g����";
		mes "����������A�����킩��ł��傤�B";
		next;
		mes "[�}���i]";
		mes "���ꂶ�ᎄ���s���Ă���I";
		mes "�`���җl�A�s���܂��傤�I";
		next;
		mes "[�W�F��]";
		mes "�s���O�ɋF�������܂��傤�B";
		mes "�_��A�ǂ�������肭�������B";
		cloakoffnpc "�}���i#ilgf03";
		cloakoffnpc "�}���i#ilgf04";
		cloakoffnpc "�}���i#ilgf05";
		cloakoffnpc "�}���i#ilgf06";
		cloakoffnpc "�}���i#ilgf07";
		cloakoffnpc "�}���i#ilgf08";
		cloakoffnpc "�}���i#ilgf09";
		chgquest 14656,14657;
		set IL_VAMP_QUE,6;
		npcskillsupport 34,10,"","";	// �u���b�V���O
		sc_start SC_BLESSING,240000,10;
		npcskillsupport 29,10,"","";	// ���x����
		sc_start SC_INCREASEAGI,240000,10;
		close;
	case 6:
		mes "[�W�F��]";
		mes "�W���r���[�ƃW���W����";
		mes "�������Ƃ����ł����ǂˁB";
		next;
		mes "[�W�F��]";
		mes "�������A��ɂȂ�̂Ȃ�A";
		mes "�}���i�ɘb�������Ă��������B";
		mes "���̏ꏊ�֑��点�܂�����B";
		close;
	case 7:
		cloakonnpc "�h���L����#ilgf02";
		cloakonnpc "�L���O#ilgf01";
		cloakonnpc "���@�g��#ilgf02";
		cloakoffnpc "���@�g��#ilgf01";
		mes "[�W�F��]";
		mes "�W���r���[�͉���̎��Â̂���";
		mes "�n��ɖ߂��܂������A";
		mes "�W���W�����܂��c�c";
		mes "�ǂ��������ł��ė~�����ł��B";
		next;
		mes "[�W�F��]";
		mes "�������A��ɂȂ�̂Ȃ�A";
		mes "�}���i�ɘb�������Ă��������B";
		mes "���̏ꏊ�֑��点�܂�����B";
		close;
	case 8:
		mes "[�W�F��]";
		mes "�W���W���̈��ۂ��S�z�ł��B";
		next;
		mes "[�W�F��]";
		mes "�������A��ɂȂ�̂Ȃ�A";
		mes "�}���i�ɘb�������Ă��������B";
		mes "���̏ꏊ�֑��点�܂�����B";
		close;
	case 14:
		mes "[�W�F��]";
		mes "�`���җl�B";
		mes "�������߂�ɂȂ��܂����H";
		next;
		menu "�݂Ȃ���̖������m�F�ł��܂�����",-;
		mes "[�W�F��]";
		mes "�������̒����̌��ʁA";
		mes "�����ł̏o�����́u�O���v�ɂ�";
		mes "^0000cd�e����^���Ȃ�^000000�悤�ł��B";
		mes "���̂Ȃ̂��͂킩��܂��񂪁A";
		mes "�K���Ȃ��Ƃł��B";
		next;
		mes "[�W�F��]";
		mes "�������Ď��͕K�v�ł��B";
		mes "�`���җl�Ȃ�";
		mes "���������Ă��������܂���ˁH";
		mes "�O�����i�Ղɂ������`���Ă��������B";
		next;
		menu "�������A�ӊO�ł����B",-;
		mes "[�}���i]";
		mes "���@���p�C�A��";
		mes "�����������邩�Ǝv���܂������H";
		mes "�����Ȃ�A���̒ʂ�ł��I";
		next;
		mes "[�W�F��]";
		mes "�����ł��B";
		mes "�����ɏ]���Ȃ炻���Ȃ�܂��ˁB";
		mes "�������ނ�����Ă�����c�c";
		mes "�łڂ��ׂ��ΏۂȂ̂��H";
		mes "�Ƃ����^�₪�����т܂����B";
		next;
		mes "[�W�F��]";
		mes "���������l�q���݂�K�v������܂��B";
		next;
		emotion 36,"�}���i#ilgf01";
		mes "[�}���i]";
		mes "������Ƃł��ԈႢ��Ƃ�����A";
		mes "�������A�|���܂��I";
		next;
		emotion 33,"�A���g���[�k#ilgf01";
		mes "[�A���g���[�k]";
		mes "�͂��A��������Ȏ���������A";
		mes "���̕��܂Ŏv������";
		mes "�\��Ă��������ˁB";
		next;
		mes "[�W�F��]";
		mes "����ł̓O�����i�Ղ�";
		mes "��낵���`���Ă����Ă��������B";
		mes "�����l�ł����B";
		chgquest 14665,14666;
		set IL_VAMP_QUE,15;
		close2;
		warp "gef_dun01.gat", 133, 219;
		end;
	case 15:
		mes "[�W�F��]";
		mes "�O�����i�ՂɁA";
		mes "�����Ɏc��Ɠ`���Ă��������B";
		next;
		mes "[�W�F��]";
		mes "�O�ɏo��ɂ�";
		mes "�}���i�ɗ���ł��������B";
		close;
	}
}

gef_d01_i.gat,112,228,5	script	�}���i#ilgf01	746,{
	mes "[�}���i]";
	mes "���̏ꏊ�ɖ߂�܂����H";
	next;
	if(select("�͂�","������") == 2) {
		mes "[�}���i]";
		mes "�킩��܂����B";
		mes "�߂鎞�͂��ł�";
		mes "���������Ă��������B";
		close;
	}
	mes "[�}���i]";
	mes "�����ɂ����ӂ��������B";
	close2;
	warp "gef_dun01.gat", 133, 219;
	end;
}

gef_d01_i.gat,93,178,5	script	�}���i#ilgf03	746,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 6) end;
	unittalk getnpcid(0,"�}���i#ilgf03"),"�}���i : ���̕���������ȋC�z�������܂��B�����s���Ă݂܂��傤�I";
	if(!sleep2(1500)) end;
	misceffect 304,"�}���i#ilgf03";
	cloakonnpc "�}���i#ilgf03";
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,127,153,5	script	�}���i#ilgf04	746,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 6) end;
	unittalk getnpcid(0,"�}���i#ilgf04"),"�}���i : ���̕��̋C�z�������i�X�����Ȃ�܂��B�}���ł��������I";
	if(!sleep2(1500)) end;
	misceffect 304,"�}���i#ilgf04";
	cloakonnpc "�}���i#ilgf04";
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,213,237,5	script	�}���i#ilgf05	746,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 6) end;
	unittalk getnpcid(0,"�}���i#ilgf05"),"�}���i : ��̕���������ȋC�z�������܂��B�}���ł��������I";
	if(!sleep2(1500)) end;
	misceffect 304,"�}���i#ilgf05";
	cloakonnpc "�}���i#ilgf05";
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,150,224,5	script	�}���i#ilgf06	746,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 6) end;
	unittalk getnpcid(0,"�}���i#ilgf06"),"�}���i : ���̕���������ȋC�z�������܂��B�����s���Ă݂܂��傤�I";
	if(!sleep2(1500)) end;
	misceffect 304,"�}���i#ilgf06";
	cloakonnpc "�}���i#ilgf06";
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,208,144,5	script	�}���i#ilgf07	746,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 6) end;
	unittalk getnpcid(0,"�}���i#ilgf07"),"�}���i : �C�z���߂Â��Ă��܂��I�@���Ə������ł��I";
	if(!sleep2(1500)) end;
	misceffect 304,"�}���i#ilgf07";
	cloakonnpc "�}���i#ilgf07";
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,250,130,5	script	�}���i#ilgf08	746,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 6) end;
	unittalk getnpcid(0,"�}���i#ilgf08"),"�}���i : �k�֍s���Ă݂܂��傤�I";
	if(!sleep2(1500)) end;
	misceffect 304,"�}���i#ilgf08";
	cloakonnpc "�}���i#ilgf08";
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,255,202,5	script	�}���i#ilgf09	746,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 6) end;
	unittalk getnpcid(0,"�}���i#ilgf09"),"�}���i : �쑤�֍s���Ă݂܂��傤�I";
	if(!sleep2(1500)) end;
	misceffect 304,"�}���i#ilgf09";
	cloakonnpc "�}���i#ilgf09";
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,116,228,3	script	�A���g���[�k#ilgf01	669,{
	if(IL_VAMP_QUE <= 5) {
		mes "[�A���g���[�k]";
		mes "�V�X�^�[�W�F���A";
		mes "�l�̘b�𕷂��Ă��������I";
		close;
	}
	else if(IL_VAMP_QUE == 6) {
		mes "[�A���g���[�k]";
		mes "��l�̂��������F���Ă܂����c�c";
		mes "�����S�z�ł��B";
		mes "������������ł��傤���B";
		close;
	}
	else if(IL_VAMP_QUE == 7) {
		mes "[�A���g���[�k]";
		mes "�W���W���͂܂��ł���ˁH";
		mes "�����S�z�ł��ˁB";
		mes "�W���r���[����͎��Â̂��߁A";
		mes "�n��ɖ߂�܂����B";
		close;
	}
	mes "[�A���g���[�k]";
	mes "�����͋����[���������߂���";
	mes "��������������ǂ���";
	mes "�Y�܂����ł��ˁB";
	close;
}

gef_d01_i.gat,250,164,5	script	�i��#ilgf01	110,5,5,{
	if(IL_VAMP_QUE == 6) {
		mes "[�i��]";
		mes "�������ȁB";
		mes "�������ꂶ�ᓮ���Ȃ����A";
		mes "�C�͂��Ȃ���";
		mes "�e���|�[�g���ł��Ȃ����c�c�B";
		next;
		emotion 28,"�i��#ilgf01";
		mes "[�i��]";
		mes "�͂��I";
		mes "�܂����A����ŏI��肩�H";
		mes "���ʂ̂��H";
		mes "���ʂ��낤�ˁc�c����ȏꏊ�Łc�c�B";
		if(!sleep2(1000)) end;
		cloakoffnpc "�A���f�b�h#ilgf08";
		cloakoffnpc "�A���f�b�h#ilgf09";
		unittalk getnpcid(0,"�A���f�b�h#ilgf08"),"�A���f�b�h : �O�����������c�c�B";
		unittalk getnpcid(0,"�A���f�b�h#ilgf09"),"�A���f�b�h : �������������c�c�B";
		next;
		mes "[�i��]";
		mes "���႟�[�I";
		mes "�܂����ꂽ�I";
		mes "�����āc�c�B";
		next;
		menu "�T�^�I�Ȏi�Ղ̕����c�c�H",-;
		misceffect 304,"�}���i#ilgf10";
		cloakoffnpc "�}���i#ilgf10";
		unittalk getnpcid(0,"�}���i#ilgf10"),"�}���i : ����ȂƂ���ɋ��܂������H";
		next;
		mes "[�}���i]";
		mes "�W���r���[�I";
		next;
		mes "[�W���r���[]";
		mes "���A�}���i����I";
		mes "�����Ă��������I";
		mes "�}���i���񂪌�����Ȃ����߂ɂ��A";
		mes "���������āI";
		if(!sleep2(1000)) end;
		misceffect 315,"�i��#ilgf01";
		next;
		mes "[�}���i]";
		mes "�S�Ă̎��l������y�ցI";
		unittalk getnpcid(0,"�}���i#ilgf10"),"�}���i : �^�[���A���f�b�h�I";
		if(!sleep2(1000)) end;
		misceffect 82,"�A���f�b�h#ilgf08";
		misceffect 82,"�A���f�b�h#ilgf09";
		unittalk getnpcid(0,"�A���f�b�h#ilgf08"),"�A���f�b�h : ���킠�������I";
		unittalk getnpcid(0,"�A���f�b�h#ilgf09"),"�A���f�b�h : ��������I";
		if(!sleep2(1000)) end;
		misceffect 372,"�A���f�b�h#ilgf08";
		misceffect 372,"�A���f�b�h#ilgf09";
		cloakonnpc "�A���f�b�h#ilgf08";
		cloakonnpc "�A���f�b�h#ilgf09";
		next;
		unittalk getnpcid(0,"�}���i#ilgf10"),"�}���i : ���v�ł����H";
		next;
		mes "[�}���i]";
		mes "��̂Ȃɂ���������ł��H";
		mes "�W���W������́H";
		next;
		mes "[�W���r���[]";
		mes "�W���W������Ƌ���";
		mes "���̎��ӂ𒲍����Ă܂������A";
		mes "�����Ă�L�m�R�𔭌�����";
		mes "�W���W������̊Ⴊ�L�����Ɓc�c�B";
		next;
		mes "[�}���i]";
		mes "���ꂾ����";
		mes "���@�g���́c�c�B";
		next;
		mes "[�W���r���[]";
		mes "�W���W������";
		mes "�L�m�R�ɐG�ꂽ�u�ԁA";
		mes "�L�m�R������������ł���B";
		next;
		mes "[�W���r���[]";
		mes "�C��������W���W�������";
		mes "���Ȃ��Ȃ��Ă��āA";
		mes "���͑������䂵��";
		mes "�����Ȃ��Ȃ��Ă�����ł���B";
		next;
		mes "[�}���i]";
		mes "�Ȃ�ƁA�L�m�R�ɂ��ꂽ��ł��ˁH";
		next;
		mes "[�W���r���[]";
		mes "�}���i����A";
		mes "�����̃L�m�R�����܂������H";
		mes "���̌���L�m�R��";
		mes "�O�̃L�m�R�Ƃ͑S�R�Ⴂ�܂��I";
		mes "�܂�Łc�c�Ԉ���ĐG�ꂽ�甚������";
		mes "�����Ȕ��e�݂����ł��B";
		next;
		menu "�C��t���Ȃ���",-;
		mes "[�}���i]";
		mes "�W���r���[����A�����܂����H";
		next;
		mes "[�W���r���[]";
		mes "��l�œ�������A�������Ă܂����ˁB";
		next;
		menu "���Ȏ��Â��Ȃ���ł����H",-;
		mes "[�}���i]";
		mes "�������͐��E�҂Ƃ��Ă�";
		mes "��{�I�ȌP���͂��܂����A";
		mes "��Ȕ\�͂͊e���ňقȂ�܂��B";
		next;
		mes "[�W���r���[]";
		mes "���̓��ӂ͐��̂ł��B";
		mes "�I�[�f�B���̈ӂ��]���L�߂邱�Ƃ��A";
		mes "���̊�тł��萶�������Ȃ�ł��B";
		next;
		mes "[�}���i]";
		mes "�ڋ��ɂȂ�Ȃ��ł��������B";
		mes "�W���r���[����̉̂𕷂��ƁA";
		mes "�E�C�Ɨ͂��N���ė��܂��B";
		mes "�����炱�̃Q�t�F���܂�";
		mes "���ɎQ��ꂽ��ł���B";
		next;
		mes "[�}���i]";
		mes "�`���җl�A���̓W���r���[�����";
		mes "�V�X�^�[�W�F���̂���Ƃ���܂�";
		mes "�A��čs���܂�����A";
		mes "���ӂ�T���Ă݂Ă��������B";
		mes "�W���r���[��A��߂�����A";
		mes "�����ɍ������܂��B";
		next;
		mes "[�W���r���[]";
		mes "���C�����āB";
		mes "�����ɂ̓m�[�g�̎�����̋L����";
		mes "�f���I�Ɍ���Ă͏������肵�܂��B";
		mes "���Ӑ[�����ĂȂ��ƁA";
		mes "���ɘf�킳��邩���m��܂���B";
		next;
		mes "[�W���r���[]";
		mes "�������c�c";
		mes "�׈��ȋC�z�܂Ŋ������܂��B";
		mes "�ǂ����C�����āc�c�B";
		next;
		mes "[�}���i]";
		mes "�W���r���[����A�s���܂��傤�B";
		next;
		mes "�]�c��̈�l�A";
		mes "�@�W���W�������T�����]";
		misceffect 304,"�}���i#ilgf10";
		misceffect 304,"�i��#ilgf01";
		cloakonnpc "�}���i#ilgf10";
		cloakonnpc "�}���i#ilgf03";
		cloakonnpc "�}���i#ilgf04";
		cloakonnpc "�}���i#ilgf05";
		cloakonnpc "�}���i#ilgf06";
		cloakonnpc "�}���i#ilgf07";
		cloakonnpc "�}���i#ilgf08";
		cloakonnpc "�}���i#ilgf09";
		cloakonnpc "�i��#ilgf01";
		cloakoffnpc "���@�g��#ilgf25";
		cloakoffnpc "���@�g��#ilgf26";
		cloakoffnpc "�A���f�b�h#ilgf01";
		cloakoffnpc "���@�g��#ilgf24";
		cloakoffnpc "����L�m�R#ilgf01";
		cloakoffnpc "���@�g��#ilgf23";
		cloakoffnpc "�����A���f�b�h#ilgf01";
		cloakoffnpc "���@�g��#ilgf21";
		cloakoffnpc "���@�g��#ilgf22";
		cloakoffnpc "�A���f�b�h#ilgf02";
		cloakoffnpc "�A���f�b�h#ilgf03";
		cloakoffnpc "�A���f�b�h#ilgf04";
		cloakoffnpc "���@�g��#ilgf19";
		cloakoffnpc "���@�g��#ilgf20";
		cloakoffnpc "�A���f�b�h#ilgf05";
		cloakoffnpc "���@�g��#ilgf18";
		cloakoffnpc "�N���̖�#ilgf18";
		cloakoffnpc "���@�g��#ilgf16";
		cloakoffnpc "���@�g��#ilgf17";
		cloakoffnpc "���@�g��#ilgf12";
		cloakoffnpc "���@�g��#ilgf13";
		cloakoffnpc "����������#ilgf02";
		cloakoffnpc "���@�g��#ilgf11";
		cloakoffnpc "���@�g��#ilgf09";
		cloakoffnpc "���@�g��#ilgf10";
		cloakoffnpc "���@�g��#ilgf08";
		cloakoffnpc "����������#ilgf03";
		cloakoffnpc "���@�g��#ilgf06";
		cloakoffnpc "���@�g��#ilgf07";
		cloakonnpc "�A���f�b�h#ilgf06";
		cloakoffnpc "���@�g��#ilgf27";
		cloakoffnpc "���@�g��#ilgf28";
		chgquest 14657,14658;
		set IL_VAMP_QUE,7;
		close;
	}
	end;
OnTouch:
	if(IL_VAMP_QUE == 6)
		unittalk getnpcid(0,"�i��#ilgf01"),"�i�� : �{���ɍ������ȁc�c�B";
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,253,165,3	script	�}���i#ilgf10	746,{
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,254,162,1	script	�A���f�b�h#ilgf08	3752,{
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,252,160,1	script	�A���f�b�h#ilgf09	3753,{
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,250,164,0	script	#ilgf06	139,15,15,{
	if(IL_VAMP_QUE == 6)
		cloakoffnpc "�i��#ilgf01";
	if(IL_VAMP_QUE == 7)
		cloakonnpc "�i��#ilgf01";
	end;
}

gef_d01_i.gat,81,135,5	script	���@�g��#ilgf01	10224,{
	switch(IL_VAMP_QUE) {
	case 7:
		mes "[���@�g��]";
		mes "����́c�c";
		mes "�u���̂��Ƃ͂�����ƐF���Ⴄ�B";
		mes "�V�����L�m�R���ȁH";
		mes "�C�����č̂�Ȃ���c�c�B";
		next;
		menu "�W���W������H",-;
		emotion 0,"���@�g��#ilgf01";
		mes "[���@�g��]";
		mes "�c�c�I";
		mes "�l�ԁc�c�H";
		next;
		mes "[���@�g��]";
		mes "���́c�c";
		mes "�W���W���Ƃ������ł�";
		mes "����܂���B";
		next;
		mes "[���@�g��]";
		mes "��A����^0000cd�l^000000��";
		mes "������̂ł����H";
		next;
		mes "[���@�g��]";
		mes "�c�c�B";
		next;
		emotion 23,"";
		menu "�c�c�l�Ԃ���Ȃ��̂ł����H",-;
		mes "[���@�g��]";
		mes "���A�����c�c�B";
		next;
		mes "[�{�~]";
		mes "���́c�c���̖��O��";
		mes "^0000cd�{�~^000000�Ƃ����܂��B";
		mes "���T���̐l�łȂ���";
		mes "�\���󂠂�܂���B";
		next;
		menu "���Ȃ��̃m�[�g�����܂����B",-;
		mes "[�{�~]";
		mes "�c�c�����ł����B";
		next;
		mes "[�{�~]";
		mes "�c�c���̃m�[�g�́A";
		mes "�����̂Ă����ł��B";
		next;
		menu "���̂���ȂƂ���ɂ���̂ł����H",-;
		mes "[�{�~]";
		mes "����́c�c";
		mes "�����A�����������痣����Ȃ�";
		mes "������������B";
		mes "�������@���p�C�A������ł��B";
		next;
		menu "���@���p�C�A�I",-;
		mes "[�{�~]";
		mes "�����ȑO�͐l�Ԃł����B";
		mes "�ł��c�c";
		mes "�M���Ă����c�c";
		mes "�F�B�����؂�����ł��B";
		next;
		mes "[�{�~]";
		mes "�l���ꐶ�����ɐ����闝�R��";
		mes "�Ȃ񂾂Ǝv���܂����H";
		mes "����́A�����ꎀ�ʂ��Ƃ�";
		mes "���߂��Ă��邩��ł��B";
		next;
		mes "[�{�~]";
		mes "���ɂ́c�c";
		mes "���̗^����ꂽ���Ԃ�";
		mes "�����Z��������ł��B";
		mes "���܂ꂽ������j���̌��t���A";
		mes "�s�g�Ȏ��̌��t�𑽂������ق�";
		mes "�n�ゾ�����̂ł��B";
		next;
		mes "[�{�~]";
		mes "�l�́A�����ɖ������̂�";
		mes "���ߓ������̂ł��B";
		mes "����^0000cd�����͂ɓ���^000000�܂����B";
		mes "�����ǎ��͑����ׂ��Ă��āA";
		mes "������ł�";
		mes "������������܂���ł����B";
		next;
		mes "[�{�~]";
		mes "�����疂�@�g���ɂȂ�����ł��B";
		mes "�g�̓I�ɋ����Ȃ��Ȃ�A";
		mes "�Ⴄ�͂ŋ����Ȃ�΂�����";
		mes "�v������ł��B";
		next;
		mes "[�{�~]";
		mes "�ł��A";
		mes "�������_�͂���ɓ����ɂ�";
		mes "�������̂��K�v���Ƃ������Ƃ�";
		mes "�m��܂���ł����B";
		next;
		mes "[�{�~]";
		mes "���@�͐��_�͂��̗͂�";
		mes "���������Ղ���̂ł��B";
		mes "�����ǂɂԂ���܂����B";
		mes "����ł����͒��߂܂���ł����B";
		mes "���̕��@��T��΂��������ł�����B";
		next;
		mes "[�{�~]";
		mes "�����A�����������Ă������";
		mes "����܂����B";
		mes "���̒��ŋ���ɔR�����鉊�B";
		mes "���ꂪ����l�Ƃ���";
		mes "�������炦�������̂ł��B";
		next;
		mes "[�{�~]";
		mes "����Ȃ�����A";
		mes "�����Ől�Ԃł͂Ȃ�";
		mes "^0000cd�قȂ鑶��^000000�ɏo��������ł���B";
		next;
		mes "�]�{�~�͂�����ƌ��t��";
		mes "�@�I��ł�悤�������B";
		mes "�@�l�����܂Ƃ߂���̂�҂��āA";
		mes "�@������x�b�������悤�]";
		chgquest 14658,14659;
		set IL_VAMP_QUE,8;
		close;
	case 8:
		mes "[�{�~]";
		mes "�����ɂ͉����Z��ł��邩";
		mes "�m���Ă��܂����H";
		next;
		mes "[�{�~]";
		mes "�i�C�g���A�A�L�m�R�A�]���r�c�c";
		mes "�����Ă����ЂƂc�c";
		mes "�h���L�����ł��B";
		next;
		mes "[�{�~]";
		mes "�ނƏ��߂ĉ�������A";
		mes "�܂��ɏ��ł��鐡�O�ł����B";
		next;
		mes "[�{�~]";
		mes "���̎�X�����p��";
		mes "���͎������d�˂Ă����̂���";
		mes "����܂���B";
		next;
		mes "[�{�~]";
		mes "�c�c������A";
		mes "�߂Â��Ă͂����Ȃ���";
		mes "�m��Ȃ�����A���͎����̌���";
		mes "�ނɕ����^���Ď��Â����̂ł�";
		next;
		mes "[�{�~]";
		mes "���ꂩ�玄������";
		mes "���X��悤�ɂȂ�A";
		mes "���X�ɐe�����Ȃ�܂����B";
		mes "���ɗF�B���o�����̂�";
		mes "���ꂪ���߂Ă�������ł��B";
		next;
		mes "[�{�~]";
		mes "�c�c�B";
		next;
		mes "[�{�~]";
		mes "�c�c";
		mes "�c�c�c�c�B";
		next;
		misceffect 496,"�h���L����#ilgf01";
		misceffect 1003,"�h���L����#ilgf01";
		cloakoffnpc "�h���L����#ilgf01";
		if(!sleep2(4000)) end;
		unittalk getnpcid(0,"�h���L����#ilgf01"),"�h���L���� : ���̉����������H";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"���@�g��#ilgf01"),"�{�~ : ����́c�c������Ɛ������Â炢��B�����A�l�Ƃ͂����������̂Ȃ́B";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"�h���L����#ilgf01"),"�h���L���� : �N�͂���܂ŏo������l�Ԃ����Ƃ͈Ⴄ�ȁB�ނ�͉������ł����悤�Ƃ����B";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"���@�g��#ilgf01"),"�{�~ : ���ꂼ��Ⴄ�̂��A�l�ԂƂ������̂Ȃ̂�B";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"�h���L����#ilgf01"),"�h���L���� : ����Ƀv���[���g��������悤�B�N�͋������̂ƒ����������~���������͂����ȁB";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"���@�g��#ilgf01"),"�{�~ : �����A�ł��ǂ�����āc�c";
		if(!sleep2(2000)) end;
		unittalk getnpcid(0,"���@�g��#ilgf01"),"�{�~ : �܂����c�c�H�@����A��΁I";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"�h���L����#ilgf01"),"�h���L���� : �~�����̂��낤�B�Ⴄ���H�@�����炱��ȏ��ɂ܂ŗ��Č��������Ă����񂶂�Ȃ��̂��H";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"���@�g��#ilgf01"),"�{�~ : �~�������I�@�N�����I";
		if(!sleep2(2000)) end;
		unittalk getnpcid(0,"���@�g��#ilgf01"),"�{�~ : �ł��c�c�l�ł��邱�Ƃ��̂ĂĂ܂ŁA��ɓ��ꂽ���Ƃ͎v��Ȃ���I";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"�h���L����#ilgf01"),"�h���L���� : �����|���Ȃ��̂��H�@�N�Ɏc���ꂽ���Ԃ͎c��͂������c�c�B";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"���@�g��#ilgf01"),"�{�~ : ���̋��|�����邩�炱���A���͍���������Đ����Ă���B���̋��|�����̎��������ɂ������Ă���́B";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"���@�g��#ilgf01"),"�{�~ : �������ł��邱�Ƃ���߂āA�͂𓾂Ă��܂�����A�ߋ��̎��⎄�̍s���A���̎�肽���������̑S�Ă�ے肷�邱�ƂɂȂ�́B";
		if(!sleep2(4000)) end;
		unittalk getnpcid(0,"���@�g��#ilgf01"),"�{�~ : ����͎�����蔲���Ă����A���Ƃ����l�Ԃ���߂邱�Ƃɓ������̂�I";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"�h���L����#ilgf01"),"�h���L���� : �N�����Ɠ����ɂȂ����Ƃ��Ă��A�N�͌N���낤�B";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"���@�g��#ilgf01"),"�{�~ : ����������肶��Ȃ��́B";
		if(!sleep2(2000)) end;
		unittalk getnpcid(0,"���@�g��#ilgf01"),"�{�~ : ���͎�������Ă���B��������ꐶ�����ɐ����悤�Ƃ���l�ԂƂ��Ă̎�����葱�������́B";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"�h���L����#ilgf01"),"�h���L���� : �������c�c�B�N�̖��������Ă����̂����߂����̂́A�ƂĂ��ɂ������̂��B";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"�h���L����#ilgf01"),"�h���L���� : �����N����肽���Ƃ������̂𑸏d����Ƃ��悤�B���ɂ͗����ł��Ȃ����ˁB";
		if(!sleep2(3000)) end;
		mes "[�{�~]";
		mes "�c�c�B";
		next;
		mes "[�{�~]";
		mes "�ނ͎���^0000cd��^000000���܂����B";
		mes "�����ǂ�����A";
		mes "���̏ꏊ��K�ꂽ�l������";
		mes "�����ɂȂ�c�c�B";
		next;
		mes "[�{�~]";
		mes "�C��������A";
		mes "���͂���ȉ������ɂȂ��Ă܂����B";
		mes "�ނ͖񑩂�j������ł��B";
		next;
		if(!sleep2(1000)) end;
		unittalk getnpcid(0,"���@�g��#ilgf01"),"�{�~ : �����������ɂ����̂ˁH";
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"�h���L����#ilgf01"),"�h���L���� : �c�c���܂Ȃ��B";
		if(!sleep2(2000)) end;
		misceffect 496,"�h���L����#ilgf01";
		cloakonnpc "�h���L����#ilgf01";
		if(!sleep2(1000)) end;
		mes "[�{�~]";
		mes "�{���ɑ��������B";
		mes "�c�c�M���Ă����F�B�������̂ɁB";
		next;
		mes "[�{�~]";
		mes "�O�ł͎��͓ˑR���H���Ă��܂���";
		mes "�l�ԂɂȂ��Ă���ł��傤�ˁH";
		mes "�ǂꂮ�炢�̎��Ԃ�";
		mes "�o������ł��傤�H";
		next;
		mes "[�{�~]";
		mes "���邢�́c�c";
		mes "���͍ŏ����炢�Ȃ������݂�����";
		mes "�Y�ꋎ��ꂽ��ł��傤���B";
		mes "�ƂĂ��߂����ł��B";
		next;
		mes "[�{�~]";
		mes "�����ǁA����ł�";
		mes "�������g�����������Ɗ�����u�Ԃ�";
		mes "�}�ɖK��܂��B";
		mes "���̋Q���Ɗ����ɑς��Ă���ƁA";
		mes "���͖{���̉������ɂȂ��Ă��܂��B";
		next;
		mes "[�{�~]";
		mes "�ł��A�������������邽�߂�";
		mes "�O�֏o��΁c�c";
		mes "�����ƒN����";
		mes "�Q���Ă��܂��ł��傤�ˁB";
		next;
		menu "�ǂ�����č��܂őς��؂ꂽ��ł����H",-;
		mes "[�{�~]";
		mes "���͑���Ȃ��̗͂�₤���߂�";
		mes "�����ƌ������Ă���";
		mes "^0000cd��i�����Ɋւ���m��^000000������܂��B";
		next;
		mes "[�{�~]";
		mes "���̕ӂŎ�ɓ��镨�ŁA";
		mes "�U���̌��t�����o����";
		mes "���̓����̓���ς��Ă��܂��B";
		mes "^0000cd�l�Ԃ̐^��^000000�����Ă���U���Ȃ�ł��B";
		mes "�������ɖ{���̐l�Ԃ�";
		mes "����c���Ă܂���B";
		next;
		mes "[�{�~]";
		mes "�c�c���߂�Ȃ����B";
		mes "�ދ��Șb�ł����ˁH";
		next;
		mes "[�{�~]";
		mes "���́A�`���җl�B";
		mes "�\����Ȃ��̂ł����A";
		mes "����݂��Ƃ����Ă�";
		mes "��낵���ł��傤���H";
		next;
		menu "�ǂ��ł���",-;
		mes "[�{�~]";
		mes "����ȊȒP�Ɉ����󂯂���";
		mes "�댯�ł���B";
		mes "��������v��������";
		mes "�ǂ��������ł����H";
		emotion 4,"";
		next;
		mes "[�{�~]";
		mes "�ӂӁc�c��k�ł��B";
		mes "�U���̌������ޗ���";
		mes "�T���Ă�����ł����A";
		mes "���͂��̃L�m�R��";
		mes "�ώ@���Ȃ��Ă͂����܂���B";
		next;
		mes "[�{�~]";
		mes "���߂Č����ނȂ̂ŁA";
		mes "�o���邾���V�N�ȏ�Ԃ�";
		mes "�ώ@����������ł��B";
		mes "�Ȃ̂ł����𗣂���܂���B";
		next;
		menu "�����K�v�ł����H",-;
		mes "[�{�~]";
		mes "���肪�Ƃ��������܂��B";
		mes "�U���̌������ɂ�";
		mes "�ׂƂׂƂ��錌�ƁA";
		mes "���̂��̔S�t���K�v�Ȃ�ł��B";
		next;
		mes "[�{�~]";
		mes "^0000cd�}�b�g�h���C�����A�[��";
		mes "�ׂƂׂƂ��錌��1�A";
		mes "�u���̂���";
		mes "���̂��̔S�t��1��^000000�~�����ł��B";
		mes "��낵�����肢���܂��B";
		chgquest 14659,14660;
		set IL_VAMP_QUE,9;
		close;
	case 9:
		mes "[�{�~]";
		mes "�ޗ����W�߂ė��Ă��ꂽ��ł����H";
		mes "�ǂ�ǂ�c�c�B";
		next;
		if(countitem(25268) < 1 || countitem(25269) < 1) {
			mes "[�{�~]";
			mes "���A�܂��r���݂����ł��ˁB";
			next;
			mes "[�{�~]";
			mes "^0000cd�}�b�g�h���C�����A�[��";
			mes "�ׂƂׂƂ��錌��1�A";
			mes "�u���̂���";
			mes "���̂��̔S�t��1��^000000�~�����ł��B";
			mes "��낵�����肢���܂��B";
			close;
		}
		mes "[�{�~]";
		mes "���ꂾ������Ώ\���ł��B";
		mes "�{���ɂ��肪�Ƃ��B";
		next;
		mes "[�{�~]";
		mes "�L�m�R�͂悭���Ă݂���A";
		mes "�ʂɉ��l�̖������̂ł����B";
		mes "����ӂꂽ���ʂ̃L�m�R�c�c�B";
		next;
		menu "���t�͂ǂ�����č��܂����H",-;
		mes "[�{�~]";
		mes "�}�b�g�h���C�����A�[��";
		mes "���l�̌����z���Đ����Ă܂��B";
		next;
		mes "[�{�~]";
		mes "�������̌��͓Ő���������ł��B";
		mes "�����ł��̃L�m�R�Œ��a�����܂��B";
		next;
		mes "[�{�~]";
		mes "����ȕ��ɁI";
		misceffect 305,"���@�g��#ilgf01";
		next;
		mes "[�{�~]";
		mes "�������̔S�t�ł�";
		mes "�ł����S�ɂ͎�菜���܂���B";
		mes "������ł��̓���";
		mes "���ȏ㒙�܂�Ǝ��X�c�c�B";
		next;
		menu "�A���P�~�X�g�̍˔\������܂���",-;
		mes "[�{�~]";
		mes "�ŏ��i�H�����߂����́A";
		mes "����ȍ˔\������Ƃ�";
		mes "�m��܂���ł����B";
		mes "�������Ԃ�����������A";
		mes "�����Ȃ��Ƃ��������͂������A";
		mes "�Ⴄ����I�񂾂����m��܂���ˁB";
		next;
		mes "[�{�~]";
		mes "���A�������B";
		mes "�l��T���Ă����ł�����ˁH";
		mes "�W���W������ł��������H";
		next;
		mes "[�{�~]";
		mes "�ŋ߁A���̕ӂ�Ől�Ԃ�";
		mes "�������Ƃ͂Ȃ��ł����c�c";
		mes "��������������A";
		mes "�T���Ă�l�������Ɠ`���܂��ˁB";
		next;
		mes "[�{�~]";
		mes "�����������ė~�����ł��B";
		mes "�����ɂ���̂�";
		mes "�������ł͂Ȃ��ł�����B";
		mes "�܂�������Ȃ��Ƃ�����A";
		mes "������������A�������Ɂc�c�B";
		next;
		mes "[�{�~]";
		mes "����A�Ȃ�ł��Ȃ��ł��B";
		mes "�����ƌ�����Ǝv���܂��B";
		mes "�ǂ����Ă�������Ȃ��Ȃ�A";
		mes "�쑤�̂���߂���";
		mes "�T���Ă݂Ă��������B";
		next;
		mes "[�{�~]";
		mes "�}���������ǂ��Ǝv���܂��B";
		mes "����ł́B";
		cloakoffnpc "�h���L����#ilgf02";
		cloakoffnpc "�L���O#ilgf01";
		cloakoffnpc "���@�g��#ilgf02";
		delitem 25268,1;
		delitem 25269,1;
		chgquest 14660,14661;
		set IL_VAMP_QUE,10;
		close;
	case 10:
	case 11:
		mes "[�{�~]";
		mes "����������Ƃ����ł��ˁB";
		mes "�ǂ����Ă�������Ȃ��Ȃ�A";
		mes "�쑤�̂���߂���";
		mes "�T���Ă݂Ă��������B";
		close;
	case 12:
		mes "[�{�~]";
		mes "����āI";
		mes "���͂��Ȃ�������";
		mes "��Q�͉�������͂��Ȃ���I";
		next;
		mes "[�}���i]";
		mes "���Ɏ������̒��Ԃ���l�������I";
		mes "���񂽂̎d�Ƃ���H";
		next;
		mes "[�{�~]";
		mes "���͍��܂ŒN��";
		mes "�����Ă��Ȃ��������A";
		mes "���ꂩ������������͂Ȃ���B";
		next;
		mes "[�}���i]";
		mes "�������Ɋ�Q�������Ȃ��Ƃ��Ă��A";
		mes "���Ȃ��̑��݂͏����ē��R��I";
		mes "���Ȃ��̑��݂��̂��̂��A";
		mes "�_�̈ӎu�ɋt����Ă�����́I";
		next;
		mes "[�{�~]";
		mes "�_�̈ӎu�H";
		mes "�_�͑S�Ă�������B";
		mes "���Ȃ������͂��������ĂȂ������H";
		next;
		mes "[�}���i]";
		mes "���҂͓y�̒���";
		mes "���炬������񂾁I";
		mes "���Ȃ��͎����̑��݂�";
		mes "�����Ǝv���Ă���́H";
		next;
		mes "[�{�~]";
		mes "�c�c�ł��A�ł��I";
		mes "���͖{���ɉ������Ă��Ȃ��I";
		next;
		mes "[�}���i]";
		mes "�����A";
		mes "���ꂩ�����΂��Ȃ��Ƃ���";
		mes "�ۏ؂͖����I";
		next;
		mes "[�W�F��]";
		mes "�}���i����A���������āB";
		next;
		mes "[�}���i]";
		mes "�S�O�����ƂȂǂ���܂���I";
		mes "���҂͓y�ցI";
		mes "�A���g���[�k����I";
		next;
		mes "[�A���g���[�k]";
		mes "�d������܂���ˁB";
		mes "�}���i����̌������Ƃ�";
		mes "�ꗝ����܂����B";
		next;
		mes "[�}���i]";
		mes "��炦���I";
		unittalk getnpcid(0,"�}���i#ilgf02"),"���C���e�����I";
		if(!sleep2(1000)) end;
		misceffect 583,"�h���L����#ilgf03";
		cloakoffnpc "�h���L����#ilgf03";
		misceffect 318,"�h���L����#ilgf03";
		misceffect 328,"�h���L����#ilgf03";
		if(!sleep2(1000)) end;
		misceffect 668,"�h���L����#ilgf03";
		misceffect 669,"�h���L����#ilgf03";
		misceffect 791,"�h���L����#ilgf03";
		misceffect 266,"�h���L����#ilgf03";
		unittalk getnpcid(0,"�h���L����#ilgf03"),"�h���L���� : �����c�c!!";
		next;
		misceffect 583,"�L���O#ilgf02";
		cloakoffnpc "�L���O#ilgf02";
		emotion 7,"�L���O#ilgf02";
		mes "[�L���O]";
		mes "���̃o�J�I";
		mes "���ƂȂ������Ă���Ηǂ����̂��I";
		mes "�ǂ����Ă���Ȃ��Ƃ��I";
		next;
		mes "[�{�~]";
		mes "�h���L�����c�c�H";
		mes "���Ȃ����c�c���́H";
		next;
		mes "[�}���i]";
		mes "���@���p�C�A���܂����ꂽ!?";
		mes "�������ȏꏊ�Ƃ͎v�������ǁA";
		mes "���@���p�C�A�̑��A�������Ƃ́I";
		next;
		mes "[�}���i]";
		mes "�����̃R�E�����I";
		mes "���񂽂����@���p�C�A����!?";
		next;
		emotion 6,"�L���O#ilgf02";
		mes "[�L���O]";
		mes "�R�E�������ƁI";
		mes "�l�Ԃ̕Ȃɖ���ȁI";
		next;
		mes "[�W�F��]";
		mes "�҂��Ȃ����}���i����B";
		mes "�������������Ȃ����B";
		next;
		mes "[�}���i]";
		mes "�����D�@�Ȃ�ł���I";
		mes "�O�̂̂����A";
		mes "��͓̂������~�܂��Ă��܂��B";
		next;
		mes "[�W�F��]";
		mes "�����Ĉ�̂́A";
		mes "�S���U���̈ӎu�������B";
		mes "�Θb�����߂Ă��܂��B";
		next;
		mes "[�L���O]";
		mes "�Θb�����߂���āH";
		mes "�l�͈Ⴄ�I";
		mes "���������ɂ����C�͂Ȃ��I";
		misceffect 266,"�L���O#ilgf02";
		misceffect 183,"�}���i#ilgf02";
		misceffect 212,"�}���i#ilgf02";
		next;
		mes "[�}���i]";
		mes "�����c�c�I";
		mes "�ق猩�āI";
		mes "�����䖝�ł��Ȃ��I";
		next;
		misceffect 304,"�W���W��#ilgf01";
		cloakoffnpc "�W���W��#ilgf01";
		emotion 53,"�W���W��#ilgf01";
		mes "[�W���W��]";
		mes "�ӂ��A��ꂽ�B";
		mes "�݂�ȕ����̑��߂����B";
		next;
		mes "[�W���W��]";
		mes "�݂Ȃ��񗎂������āI";
		mes "������Ɨ��������Ă��������I";
		next;
		mes "[�W�F��]";
		mes "�W���W������H";
		mes "�������ł������I";
		next;
		mes "[�}���i]";
		mes "�S�R������Ȃ������̂ɁA";
		mes "�ǂ��ɍs���Ă���ł����H";
		next;
		mes "[�A���g���[�k]";
		mes "�����Ɋ������܂ꂽ��";
		mes "�����܂������A";
		mes "���͂قڎ����Ă���悤�ł��ˁB";
		next;
		mes "[�h���L����]";
		mes "�{�~�Ɏ���o���ȁc�c�B";
		mes "�{�~�Ɖ��́c�c";
		mes "�N���c�c�����Ȃ��c�c�B";
		mes "���ꂪ�����w�񂾁c�c���́B";
		next;
		mes "[�{�~]";
		mes "�h���L�����I";
		mes "�h���L����!!";
		mes "�������Â��c�c�I";
		next;
		mes "[�}���i]";
		mes "�����͂����邩�I";
		next;
		mes "[�W�F��]";
		mes "�҂��Ȃ����A�}���i����B";
		mes "��U�l�q���݂܂��傤�B";
		mes "�ނ�̓W���W�������";
		mes "���Â��Ă���܂����B";
		next;
		mes "[�}���i]";
		mes "���ꂪ㩂��Ƃ�����H";
		next;
		mes "[�W�F��]";
		mes "������U�����Ă����Ƃ��Ă��A";
		mes "���ł͂����炪�D���ł��B";
		next;
		mes "[�A���g���[�k]";
		mes "�l���V�X�^�[�W�F���̍l����";
		mes "���ӂ��܂��B";
		mes "����ȋ߂��Ō�����@���";
		mes "�ő��ɂȂ����Ƃł����B";
		next;
		mes "[�W�F��]";
		mes "�{�~����c�c�ł�����ˁH";
		mes "�m�[�g��ǂ݂܂����B";
		mes "��������������������ł����H";
		mes "���̃��@���p�C�A������";
		mes "���Ȃ̂ł����H";
		next;
		menu "����́A���������������܂��B",-;
		mes "�]�V�X�^�[�E�W�F���̈�s��";
		mes "�@�ߋ��̃{�~�ƃh���L������";
		mes "�@�N�������Ƃ��ȒP�ɐ��������]";
		next;
		mes "[�W�F��]";
		mes "�Ȃ�قǁc�c";
		mes "����Ȃ��Ƃ��c�c�B";
		next;
		mes "[�{�~]";
		mes "�����h���L�����A";
		mes "���������ŁB";
		next;
		mes "[�}���i]";
		mes "����͒N�̌����H";
		mes "���܂����ɂ͂����Ȃ��I";
		next;
		mes "[�{�~]";
		mes "�N�̌��ł��Ȃ����I";
		mes "��������܂��Ȃ���I";
		mes "�ڂ̑O�Ől�����ɂ����Ă�̂�I";
		next;
		mes "[�}���i]";
		mes "���񂽂�͐l�ł͂Ȃ��I";
		next;
		mes "[�L���O]";
		mes "�����A�o�J�Ȃ�炾�B";
		mes "�����͖l�����Ă邩��A";
		mes "�������Â���B";
		next;
		mes "[�W���W��]";
		mes "������`���܂��B";
		next;
		mes "[�W�F��]";
		mes "���Â��Ă����Ă��������B";
		next;
		emotion 0,"�}���i#ilgf02";
		mes "[�}���i]";
		mes "���@���p�C�A��!?";
		mes "�V�X�^�[�W�F���͎�������";
		mes "���[�_�[����Ȃ��ł����I";
		mes "�`����a���ɂ������ł����H";
		next;
		mes "[�W���W��]";
		mes "�}���i����A�ނ炪�N���낤���A";
		mes "���͏����Ă��������ł��B";
		mes "���̌��Ԃ���Ȃ��B";
		next;
		mes "[�W���W��]";
		mes "���@���p�C�A���l�Ԃ�������̂�";
		mes "�s�v�c��������ł����A";
		mes "���Ȃ�킩��܂��B";
		mes "�h���L��������͔ޏ�����";
		mes "�w�񂾂�ł��ˁA�l�ԂƂ������̂��B";
		next;
		mes "[�W���W��]";
		mes "�h���L���������";
		mes "�l�Ԃ𗝉��������ƌ����Ă܂����B";
		mes "�{�~�����ʂ��ĂˁB";
		mes "������������ł́A";
		mes "�l�Ԃ������ɗ������Ă��܂��B";
		next;
		mes "[�W���W��]";
		mes "����Ɋׂ������l���A";
		mes "�ŎZ�������ɏ����悤�Ƃ���";
		mes "�����ł��Ȃ��s���B";
		mes "���ꂱ����Ԑl�Ԃ炵��";
		mes "�S�ł͂Ȃ��ł��傤���H";
		next;
		mes "[�W���W��]";
		mes "���l�𗝉���������̂́A";
		mes "���ꂪ�N���낤�Ɗ֌W����܂���B";
		mes "�}���i����͖ڂ̑O�Ől�����ʂ̂�";
		mes "�����Ă����܂����H";
		next;
		mes "[�}���i]";
		mes "����͑��肪�l�Ԃ̏ꍇ�̂�";
		mes "�����邱�Ƃł���I";
		mes "�ނ�̓��@���p�C�A�Ȃ�ł��I";
		next;
		mes "[�L���O]";
		mes "�h���L�������ǂ����Ă���ȕ���";
		mes "�Ȃ����̂�����Ƃ킩�����B";
		mes "���@�g���A";
		mes "�N�̌��t�𕷂������炾�ȁB";
		mes "�S���h���L�����̋Y������";
		mes "�v���Ă�����B";
		next;
		mes "[�L���O]";
		mes "�Ȃ��A�����̃����N�B";
		mes "�l�Ԃ炵���Ƃ͂Ȃ񂾁H";
		mes "���@���p�C�A�炵���Ƃ͂Ȃ񂾁H";
		mes "�����ꐶ�A��x���l�Ɋ�Q�������Ȃ�";
		mes "���@���p�C�A��������A�ǂ�����H";
		next;
		mes "[�}���i]";
		mes "�������A��������B";
		next;
		mes "[�L���O]";
		mes "���Ⴀ�A";
		mes "�����ꐶ�A���l���Q�������Ă���";
		mes "�l�Ԃ�������A�ǂ�����H";
		next;
		mes "[�}���i]";
		mes "����́c�c�@�ɑ����B";
		next;
		mes "[�L���O]";
		mes "�l�͎������鎞�A";
		mes "���̐l�Ԃ��ǂ�Ȑl�Ԃ��낤��";
		mes "�\�킸�����Ɏ���Ă����B";
		mes "���̂Ȃ�l�̓��@���p�C�A������B";
		mes "���ꂪ�l�����̝|���B";
		next;
		mes "[�L���O]";
		mes "�ނ���������B";
		mes "�������l��������A";
		mes "���ꂪ�N���낤���܂��͏�����B";
		mes "����͖{���ɒP���Ș_������Ȃ����H";
		next;
		mes "[�}���i]";
		mes "�c�c�B";
		next;
		mes "[�h���L����]";
		mes "�������c�c�{�~�H";
		next;
		mes "[�{�~]";
		mes "�h���L�����I";
		next;
		mes "[�h���L����]";
		mes "�N�͉����������̂��H";
		mes "���̎��̂悤�ɁH";
		mes "�N�͉��̏��ł�";
		mes "�]��ł�Ǝv���Ă����̂ɁB";
		next;
		mes "[�{�~]";
		mes "������c�c�B";
		mes "���Ȃ����������@���p�C�A�ɂ���";
		mes "���R���킩�����̂�B";
		mes "���Ȃ��͖ڂ̑O�Ŏ������ʂ̂�";
		mes "�ς����Ȃ������񂾂�ˁH";
		next;
		mes "[�{�~]";
		mes "�����c�c";
		mes "�����ꏏ��c�c�I";
		next;
		mes "[�h���L����]";
		mes "�{�~�c�c�B";
		next;
		mes "[�{�~]";
		mes "�h���L�����c�c�B";
		next;
		mes "[�L���O]";
		mes "���������A";
		mes "�����牽���Ă₪��H";
		next;
		mes "[�W���W��]";
		mes "�����Ƃ��Ă����܂��傤�B";
		mes "���킷���t���������Ƃł��傤�B";
		next;
		mes "[�W�F��]";
		mes "�݂Ȃ���A������ցB";
		mes "�����b�������K�v��";
		mes "���肻���ł��ˁB";
		chgquest 14663,14664;
		set IL_VAMP_QUE,13;
		close;
	case 13:
		mes "[�{�~]";
		mes "�h���L�����A";
		mes "���肪�Ƃ��B";
		mes "�����Ă��߂�Ȃ����B";
		next;
		mes "[�h���L����]";
		mes "�������N�Ƃ̖񑩂�";
		mes "�j���Ă��܂Ȃ��B";
		mes "�ǂ�Ȍ��t�ł������s�����Ȃ����A";
		mes "�{���ɂ��܂Ȃ��B";
		next;
		mes "[�{�~]";
		mes "���Ȃ�킩���B";
		mes "���Ȃ������̂���ȑI����";
		mes "���邵���Ȃ������̂��B";
		next;
		mes "[�W���W��]";
		mes "���`�ƁA������Ɨǂ��ł����H";
		mes "��l�Ƃ��A����͉����܂������H";
		mes "�h���L�����l�����͉z��������A";
		mes "���Âɂ��Ă���Α��v�ł��B";
		next;
		mes "[�h���L����]";
		mes "���܂Ȃ��A��Ԃ��������ȁB";
		next;
		mes "[�L���O]";
		mes "�ӂ�B";
		mes "�L�m�R�@���ɂ����";
		mes "��Ȃ��z���Ǝv�������A";
		mes "���\�ǂ��r�����Ă邶��Ȃ����B";
		next;
		emotion 27,"�L���O#ilgf02";
		mes "[�L���O]";
		mes "�h���L�����A�����A�낤�B";
		mes "�����𗣂�ď�֖߂�ׂ����B";
		next;
		mes "[�h���L����]";
		mes "�c�c����A";
		mes "���͂����Ɏc��B";
		next;
		mes "[�L���O]";
		mes "�͂��H�@���ŁI";
		mes "������������������Ƃ����A";
		mes "�S���I��������낤�H";
		next;
		mes "[�W�F��]";
		mes "������Ƃ����ł����H";
		mes "�������̘b��";
		mes "�����Ă���܂��񂩁B";
		next;
		mes "[�W�F��]";
		mes "���Ȃ��������N�ɂ���Q�������Ȃ�";
		mes "�Ƃ������Ƃ͂킩��܂����B";
		mes "���܂Ŗ����N�����Ă��Ȃ����Ƃ��A";
		mes "�W���W������������Ă��ꂽ���Ƃ��A";
		mes "���ׂė������܂����B";
		next;
		mes "[�W�F��]";
		mes "�������A���Ȃ������̑��݂́A";
		mes "���̋����ɔ�������̂ł��B";
		mes "�������͂��̂܂܂��Ȃ�������";
		mes "�����Ă͂����܂���B";
		next;
		emotion 7,"�L���O#ilgf02";
		mes "[�L���O]";
		mes "�h���L�����I";
		mes "������l�������ז�����C���B";
		mes "�����Ă��܂����I";
		next;
		mes "[�h���L����]";
		mes "����̓_�����B";
		mes "�@";
		mes "[�{�~]";
		mes "�_����I";
		next;
		mes "[�}���i]";
		mes "�V�X�^�[�W�F���A����ȋY����";
		mes "�M�����ɂ͂����܂���B";
		mes "�z��͂�����X��";
		mes "�U������ɈႢ����܂���I";
		mes "���̑O�ɏ������ׂ��ł��I";
		next;
		mes "[�A���g���[�k]";
		mes "�}���i�����";
		mes "�����ق��Ă��Ă��������B";
		mes "�������_�����߂��Ęb������";
		mes "������������Ⴀ��܂��񂩁H";
		mes "�l���b�����܂��傤�B";
		next;
		mes "[�A���g���[�k]";
		mes "���Ȃ��������A";
		mes "�N���Q���Ȃ����Ƃ�";
		mes "�悭�킩��܂����B";
		mes "�������A�댯�Ȑl��";
		mes "����̂������ł����c�c�B";
		next;
		emotion 6,"�L���O#ilgf02";
		mes "[�L���O]";
		mes "���Ŗl������I";
		mes "���ŁI�@���Ŗl�I";
		next;
		mes "[�A���g���[�k]";
		mes "�m���Ă��܂����ȏ�A";
		mes "�m��Ȃ��U��͏o���܂���B";
		mes "���ɉ�X���������Ă��A";
		mes "����������Ă����Ƃ�";
		mes "����܂���B";
		next;
		mes "[�A���g���[�k]";
		mes "�����ŁA�������ǂ����������A";
		mes "�������������Ɏc����";
		mes "���Ȃ�������^0000cd����낤��^000000";
		mes "���߂܂����B";
		next;
		emotion 7,"�L���O#ilgf02";
		mes "[�L���O]";
		mes "���l�������Ď�����ƌ������ȁH";
		mes "�h���L�����A�l�͂����䖝�ł��Ȃ��I";
		next;
		misceffect 389,"�L���O#ilgf02";
		misceffect 583,"�L���O#ilgf02";
		if(!sleep2(1000)) end;
		setnpcdisplay "�L���O#ilgf02",10137;
		mes "[�L���O]";
		mes "�݂�ȏ����Ă��I";
		next;
		mes "[�h���L����]";
		mes "�킩�����B";
		mes "�@";
		mes "[�{�~]";
		mes "�킩��܂����B";
		next;
		emotion 6,"�L���O#ilgf02";
		mes "[�L���O]";
		mes "����A���O��!?";
		mes "�h���L�����I";
		mes "�l�Ԃƒ��ǂ��Ȃ肷���āA";
		mes "�l�ԂɂȂ���������񂶂�Ȃ��̂��H";
		mes "�l�����̃v���C�h�ƕi�ʂ͂ǂ��ւ�����I";
		next;
		mes "[�h���L����]";
		mes "�ł͂���ŗǂ����H";
		mes "���͂��������x�܂Ȃ��ẮB";
		mes "��������肽���B";
		next;
		mes "[�W���W��]";
		mes "�����ꏏ�ɍs���܂��傤�B";
		mes "�������S�ɖ�����܂ł�";
		mes "���ɂ��܂��B";
		next;
		emotion 7,"�L���O#ilgf02";
		misceffect 389,"�L���O#ilgf02";
		misceffect 583,"�L���O#ilgf02";
		if(!sleep2(1000)) end;
		setnpcdisplay "�L���O#ilgf02",799;
		mes "[�L���O]";
		mes "�����A�C�ɓ���Ȃ��ȁB";
		mes "�h���L�����A�N���񕜂�����A";
		mes "�l�͏�ɋA���B";
		mes "�킩�����H�@�킩�������I";
		next;
		mes "[�W�F��]";
		mes "���ӂ��ꂽ�Ƃ������Ƃ�";
		mes "��낵���ł��ˁB";
		mes "�ł͎���������U�߂�܂��傤�B";
		next;
		misceffect 304,"�W�F��#ilgf02";
		if(!sleep2(1000)) end;
		cloakonnpc "�W�F��#ilgf02";
		mes "[�}���i]";
		mes "���񂽂�A";
		mes "�����������Ă�̂�Y���Ȃ�I";
		mes "�Q��Ƃ��ɂ͋C�����ȁI";
		next;
		misceffect 304,"�}���i#ilgf02";
		if(!sleep2(1000)) end;
		cloakonnpc "�}���i#ilgf02";
		mes "[�A���g���[�k]";
		mes "�ł́A�l��������Ŏ��炵�܂��B";
		next;
		misceffect 304,"�A���g���[�k#ilgf02";
		if(!sleep2(1000)) end;
		cloakonnpc "�A���g���[�k#ilgf02";
		mes "[�L���O]";
		mes "�����������I";
		mes "������I";
		mes "��x�Ɗ��������ȁI";
		mes "�l�����������s�����I";
		next;
		misceffect 583,"�L���O#ilgf02";
		if(!sleep2(1000)) end;
		cloakonnpc "�L���O#ilgf02";
		mes "[�W���W��]";
		mes "��X���s���܂��傤�B";
		mes "�������Â��ĊJ���Ȃ��ƁB";
		next;
		mes "[�h���L����]";
		mes "�{�~�A������������";
		mes "�܂��b�����悤�B";
		next;
		mes "[�W���W��]";
		mes "�����A�}���܂��傤�B";
		next;
		misceffect 304,"�W���W��#ilgf01";
		misceffect 583,"�h���L����#ilgf03";
		if(!sleep2(1000)) end;
		cloakonnpc "�W���W��#ilgf01";
		cloakonnpc "�h���L����#ilgf03";
		menu "�݂�ȍs���Ă��܂��܂����ˁB",-;
		mes "[�{�~]";
		mes "���肪�Ƃ��B";
		mes "���Ȃ��̂�������";
		mes "�N����������";
		mes "���Ԃ����߂邱�Ƃ��ł��܂����B";
		next;
		menu "���̑O�A���ɐl�ԂɌ����邩�ƕ����܂�����ˁH",-;
		mes "[�{�~]";
		mes "�c�c�����B";
		next;
		menu "�{�~����́A�N�����ƌ������Ɛl�Ԃ��Ǝv���܂��B",-;
		mes "[�{�~]";
		mes "�c�c���肪�Ƃ��B";
		mes "�N�������̌��t�������Ă���邱�Ƃ�";
		mes "���͐S����҂��]���";
		mes "�����񂾂Ǝv���܂��B";
		next;
		mes "[�{�~]";
		mes "����܂Ŏ��͉������ɂȂ�����";
		mes "�ꂵ��ł������ǁc�c";
		mes "�ȑO�̎��������Ă��Ȃ���";
		mes "�m�M���܂����B";
		mes "�p���ς���Ă��A�푰���ς���Ă��A";
		mes "���͎����ƋC�����܂����B";
		next;
		menu "����ł͕񍐂�����̂ōs���܂��ˁB",-;
		mes "[�{�~]";
		mes "�͂��B���C�����āB";
		mes "�{���ɂ��肪�Ƃ��������܂����B";
		chgquest 14664,14665;
		set IL_VAMP_QUE,14;
		close;
	case 14:
	case 15:
		mes "[�{�~]";
		mes "�񍐂͍ς񂾂̂ł����H";
		close;
	}
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,82,132,3	script	�L�m�R#ilgf01	1084,{}

gef_d01_i.gat,86,133,1	script	�h���L����#ilgf01	10137,{
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,189,98,3	script	�h���L����#ilgf02	10137,{
	switch(IL_VAMP_QUE) {
	case 10:
		mes "[�R�E����]";
		mes "�����H���Ă݂��B";
		mes "���������B";
		next;
		emotion 4,"���@�g��#ilgf02";
		mes "[���@�g��]";
		mes "����c�c���́c�c";
		mes "����͂�����Ɓc�c";
		next;
		mes "[���m��ʒj]";
		mes "�L���O�A";
		mes "�H�ׂȂ��ƌ����Ă��邾�낤�B";
		mes "���܂Ȃ��B��������Ɏӂ�B";
		next;
		mes "[���@�g��]";
		mes "���A���v�ł��B";
		next;
		mes "[�L���O]";
		mes "�������킸�Ɉꏏ�ɐH�ׂ悤���B";
		mes "�L���͂�����ƍ������ǁB";
		mes "�������ʒ�߂̐l�Ԃ���Ȃ����B";
		mes "���ꂪ������Ƒ����Ȃ邾���Ȃ̂ɁB";
		next;
		mes "[���@�g��]";
		mes "�c�c���̎���łȂ���΁A";
		mes "�������̃R�E������";
		mes "�|���Ă������ł����H";
		next;
		mes "[���m��ʒj]";
		mes "�ʖڂ��B";
		mes "���̑O�ł́A�N�����l��";
		mes "���t���Ă͂����Ȃ��B";
		next;
		emotion 6,"�L���O#ilgf01";
		mes "[�L���O]";
		mes "�l�Ԃ̂����ɐ��ӋC���ȁB";
		mes "���O�̊�ɂ�";
		mes "�l���R�E�����Ɍ����邩�H";
		next;
		mes "[���@�g��]";
		mes "�R�E��������Ȃ��ች�ł��H";
		next;
		misceffect 389,"�L���O#ilgf01";
		misceffect 583,"�L���O#ilgf01";
		if(!sleep2(1000)) end;
		setnpcdisplay "�L���O#ilgf01",10137;
		if(!sleep2(1000)) end;
		mes "[�L���O]";
		mes "����Ŗl�����Ɍ�����H";
		next;
		emotion 23,"���@�g��#ilgf02";
		mes "[���@�g��]";
		mes "�Ђ��I�@�ȁA���҂ł����I";
		next;
		mes "[�L���O]";
		mes "���ŁH";
		mes "���̎p�͋��낵���H";
		mes "�Ȃ炱��́H";
		next;
		misceffect 389,"�L���O#ilgf01";
		misceffect 583,"�L���O#ilgf01";
		if(!sleep2(1000)) end;
		setnpcdisplay "�L���O#ilgf01",735;
		if(!sleep2(1000)) end;
		emotion 28,"���@�g��#ilgf02";
		mes "[���@�g��]";
		mes "��A�����c�c��!?";
		mes "�h�A�h�A�h�b�y���Q���K�[�I";
		mes "���A�����ʖڂ��I";
		mes "���͂������ʁc�c�I";
		next;
		mes "[�L���O]";
		mes "�����Ɠ����p���|���H�@���ŁH";
		mes "�l�Ԃ͎������D���߂���";
		mes "�Ⴄ���݂�r�����邭���ɁA";
		mes "�����Ɠ����p�͎󂯓���Ȃ��H";
		next;
		mes "[���@�g��]";
		mes "���̐l�Ԃ̎p�ł��邱�ƂƁA";
		mes "�������������g�̑O��";
		mes "�����̂͑S�R�Ⴂ�܂���I";
		next;
		mes "[���m��ʒj]";
		mes "�L���O�A����ȏォ�炩���ȁB";
		next;
		emotion 54,"�L���O#ilgf01";
		mes "[�L���O]";
		mes "���񂽂͐l�ԂɊÉ߂���񂾂�B";
		next;
		misceffect 389,"�L���O#ilgf01";
		misceffect 583,"�L���O#ilgf01";
		if(!sleep2(1000)) end;
		setnpcdisplay "�L���O#ilgf01",799;
		mes "[���@�g��]";
		mes "���́c�c���������܂����A";
		mes "�����Ƃ�������������Ȃ̂ŁA";
		mes "�����s���Ă������ł���ˁH";
		next;
		mes "[���m��ʒj]";
		mes "�����B";
		mes "�@";
		mes "[�L���O]";
		mes "�_�����I";
		next;
		mes "[���m��ʒj]";
		mes "�ǂ����Ă��H�@�L���O�B";
		next;
		mes "[�L���O]";
		mes "���₢�₢��A��΃_������I";
		mes "�����͐l�Ԃ���B";
		mes "�K�����Ԃ�����͂����B";
		mes "���Ԃ��W�߂Ėl������";
		mes "�U������ɈႢ�Ȃ��I";
		mes "���̑O�̂��Ƃ�Y�ꂽ�̂��H";
		next;
		mes "[���@�g��]";
		mes "����Ȃ��Ƃ��܂����I";
		mes "���͎󂯂�����Y��Ȃ��l�Ԃł��I";
		mes "���������Ă��ꂽ�݂Ȃ����";
		mes "�Q���Ȃ��Ɛ����܂��I";
		mes "����M���Ă��������I";
		next;
		mes "[�L���O]";
		mes "�l�Ԃ͐M����ɒl���Ȃ��B";
		mes "���������������B";
		next;
		mes "[���m��ʒj]";
		mes "�L���O�A���O������";
		mes "�댯���ɂ��Ă͗������邪�A";
		mes "�l�Ԃ��M����ɒl���Ȃ�";
		mes "�Ƃ����̂ɂ͓��ӂ����˂�ȁB";
		next;
		mes "�]���ʂ̖��@�g���̕����c�c";
		mes "�@���ꂪ�W���W�����񂾂낤���]";
		next;
		menu "�W���W������ł����H",-;
		mes "[�W���W��]";
		mes "�ǁA�ǂȂ��ł��傤���H";
		next;
		mes "[�L���O]";
		mes "�ق�I�@�����̒��Ԃ����ꂽ�I";
		mes "�l���������ʂ肾�I";
		mes "�l�ԂȂǐM�p�ł��Ȃ��I";
		next;
		mes "[�W���W��]";
		mes "�Ⴂ�܂��I";
		mes "���̐l�͎��̒��Ԃ��Ⴀ��܂���I";
		mes "���߂Č���l�ł���I�@�_�ɐ����āI";
		next;
		mes "[�L���O]";
		mes "���O�̒��Ԃ���Ȃ��Ƃ��A";
		mes "���Ԃ��������l�ԂȂ񂾂�B";
		mes "���������̐l�ԁI�@������I";
		next;
		menu "�W���W������𒇊Ԃ��T���Ă��܂��B",-;
		mes "[���m��ʒj]";
		mes "�������B";
		mes "�����X�^�[�ɏP���|��Ă����̂�";
		mes "�A��Ă��Ď��Â��Ă����B";
		mes "����������͂�������A";
		mes "�A��ċA���Ă������B";
		next;
		menu "�W���W����������Â��Ă�����������ł��ˁB",-;
		mes "�]���Ȃ��͒j�Ɋ��ӂ̈ӂ�`���A";
		mes "�@�j�̖��𕷂����]";
		next;
		mes "[�L���O]";
		mes "�����܂ŗ��Ă�����";
		mes "�h���L������m��Ȃ��H";
		mes "�h���L������|�����߂�";
		mes "�����񂶂�Ȃ��̂��H";
		next;
		menu "�h���L�����H",-;
		mes "[�h���L����]";
		mes "���������΁A�`���҂����";
		mes "�o���̂������������B";
		mes "�ƂĂ��������������B";
		next;
		mes "[�h���L����]";
		mes "�Â��F�̓������B";
		mes "�������カ�F�́c�c�B";
		next;
		menu "�����ɗ���O�A�{�~����ɉ�܂����B",-;
		mes "[�h���L����]";
		mes "�������c�c�{�~�͌��C���B";
		mes "���̂��Ƃ��c�c�b�������H";
		next;
		mes "[�L���O]";
		mes "�́I";
		mes "�܂������܂ł����ɂ����̂�";
		mes "���m�炸�Ō����܂���";
		mes "���̐l�Ԃ̂��߂������̂��B";
		next;
		mes "[�W���W��]";
		mes "���`���ĉ��̂��Ƃł����H";
		next;
		mes "[�L���O]";
		mes "�c�c�B";
		next;
		mes "[�L���O]";
		mes "�c�c�i���̖����B";
		next;
		mes "[�W���W��]";
		mes "���A�i���̖��c�c!?";
		next;
		mes "[�L���O]";
		mes "�ق�I";
		mes "���ꂪ���ʂ̐l�Ԃ̔����Ȃ񂾁I";
		mes "����Ȃ̂ɂ��̐l�Ԃ�";
		mes "���m�炸������c�c�I";
		next;
		menu "�h���L�������񂪗��؂����ƌ����Ă܂����B",-;
		emotion 6,"�L���O#ilgf01";
		mes "[�L���O]";
		mes "���؂肾�ƁI";
		mes "�����A���ǂ��ɂ���H";
		mes "�������������Ԃ点�Ă�����̂ɁA";
		mes "���؂�ƌ������̂��I";
		next;
		mes "[�h���L����]";
		mes "�܂���������ł��邾�낤�B";
		mes "�������̎��̉��ɂ�";
		mes "�I���̗]�n�Ȃǖ��������c�c�B";
		next;
		menu "�������R�����肻���ł��ˁB",-;
		mes "[�h���L����]";
		mes "���������邽�߂ɂ͐l�Ԃ��K�v���B";
		mes "�l�Ԃ����̒��ɉB��A";
		mes "�K�v�Ȏ��ɐl�Ԃ����̂�";
		mes "�e�Ղ����Ƃ������B";
		next;
		mes "[�h���L����]";
		mes "��������Đ����Ă������̑O�ɁA";
		mes "�ǂ�����k�������̂��A";
		mes "����̘A�������ꂽ�B";
		mes "���`�����s����ƌ����Ȃ���A";
		mes "���ɏP���������Ă����B";
		next;
		mes "[�h���L����]";
		mes "�s�ӂ�˂����";
		mes "�������������́A";
		mes "���Ɛ��̓������Y��";
		mes "�����ɂ���ė����̂��B";
		next;
		mes "[�h���L����]";
		mes "���l�������f�r�������ŁA";
		mes "���ɍK�^�ȏo�����Ȃǂ���͂��Ȃ��B";
		mes "�����������̂��B����ȏo�������B";
		next;
		mes "[�h���L����]";
		mes "�{�~�����𐶂��Ԃ点���̂��B";
		mes "���̖������������Ԃ�Ƃ����\����";
		mes "�s�K�؂�������Ȃ����A";
		mes "�{�~�͉��Ɏ����̌���";
		mes "�����^�����̂��B";
		next;
		mes "[�h���L����]";
		mes "�������ŉ��͏��ł��邱�ƂȂ��A";
		mes "�������炦�邱�Ƃ��ł����̂��B";
		next;
		mes "[�W���W��]";
		mes "���ꂩ��ǂ�������ł����H";
		next;
		mes "[�h���L����]";
		mes "�{�~�͋������Ă͂������A";
		mes "�c���ꂽ���Ԃ͋͂������Ȃ������B";
		mes "�i���̖���^����Ƃ̉��̒�Ă�";
		mes "���ۂ������̎q�ɉ�x�ɁA";
		mes "���̖��������Ă����̂�";
		mes "���ɂ͑ς����Ȃ������B";
		next;
		mes "[�h���L����]";
		mes "�������痣��邱�Ƃ��o�������A";
		mes "�l�ԂƂ��čŌ���}�������Ƃ���";
		mes "�{�~�̈ӎu�𑸏d���A";
		mes "�Ō�����͂������Ǝv�����B";
		next;
		mes "[�h���L����]";
		mes "���͏��߂Đl�Ԃɂ��čl�����B";
		mes "�l�ԂƂ������̂��B";
		mes "���̒g�����S�ƁA";
		mes "����̗��v�Ɋւ�炸�A";
		mes "���l�������悤�Ƃ���A";
		mes "���̗������������s�����B";
		next;
		mes "[�h���L����]";
		mes "�{�~�Ɖ߂����Ă����";
		mes "�������悤�Ǝv�����B";
		mes "��������͑��ς�炸�s�𗝂ŁA";
		mes "�m�邱�ƂƗ������邱�Ƃ̊Ԃ�";
		mes "�[���a������̂�Ɋ������B";
		next;
		mes "[�h���L����]";
		mes "����͈ȑO�l�Ԃɑ΂���";
		mes "�����Ă����l���Ƃ́A";
		mes "�܂�ňႤ�����������B";
		mes "���͗������悤�Ɠw�͂��Ă���";
		mes "�Œ��������B";
		next;
		mes "[�W���W��]";
		mes "�Ȃ̂ɉ��́A";
		mes "�{�~����̈ӎu�ɔw������ł����H";
		next;
		mes "[�h���L����]";
		mes "���̂��������̂��B";
		mes "�������Ő��O�܂Œǂ����񂾘A�����A";
		mes "����ǂ��Ă����܂ŗ����̂��B";
		next;
		mes "[�h���L����]";
		mes "�s�^�͏�ɉ������܂Ƃ��B";
		mes "�{�~���K�^�̂��߂ɂ�";
		mes "���ɂ��ꂽ�������A";
		mes "���̕s�^�𕥂����Ƃ�";
		mes "�ł��Ȃ������B";
		next;
		mes "[�h���L����]";
		mes "���ɏ��͖����Ă������ɂƂ���";
		mes "�A���͓G�ł͂Ȃ������B";
		mes "�������{�~�݂͂�Ȃ���낤�Ƃ����B";
		mes "���Ɛl�ԁA�����̒N��l���A";
		mes "�]���ɂȂ�Ȃ��悤�ɂƁB";
		next;
		mes "[�h���L����]";
		mes "�����c�c���̐킢�̍Œ��A";
		mes "�{�~�͒v�����𕉂��Ă��܂����B";
		next;
		mes "[�h���L����]";
		mes "�ˑR�K�ꂽ�{�~�̎��ɁA";
		mes "�܂��o��ł��Ă��Ȃ���������";
		mes "�˘f���A�߂��񂾁B";
		next;
		mes "[�h���L����]";
		mes "����Ȍ`�Ń{�~��������";
		mes "�v���Ă��Ȃ��������́A";
		mes "�m�炸�m�炸�̂�����";
		mes "�{�~�𐶂��Ԃ点�Ă����B";
		mes "�{�~���]�܂Ȃ�����";
		mes "�i���̖���^���Ăȁc�c�B";
		next;
		mes "[�h���L����]";
		mes "�c�c�B";
		next;
		mes "[�W���W��]";
		mes "�h���L�����l���˘f���Ɣ߂��݂�";
		mes "�[���l����]�T���Ȃ��A";
		mes "�����Ԃ点�Ă��܂�����ł��ˁB";
		next;
		mes "[�W���W��]";
		mes "�m���Ɏ����ڂ̑O��";
		mes "��؂Ȑl������ł��܂�����A";
		mes "�����Ԃ点�邱�Ƃ��l����ł��傤�B";
		next;
		mes "[�L���O]";
		mes "�Ȃ̂ɁA���̉��m�炸�̐l�Ԃ́A";
		mes "�����񑩂�j������";
		mes "�v���Ă�񂾂�I";
		next;
		mes "[�L���O]";
		mes "�l�ɂ͗����ł��Ȃ��B";
		mes "���̎��������𐶂�����Ǝv����H";
		mes "�ǂ����ĉi���̖���^�������Ƃ��A";
		mes "���؂�ɂȂ�H";
		next;
		mes "[�W���W��]";
		mes "�l�Ԃ̎��ɂ͕�����܂��B";
		mes "�c���ꂽ���Ԃ��Z�����A";
		mes "���ꐶ���������悤��";
		mes "���Ă����̂ł��傤�B";
		mes "���ɂ��������̎��Ԃ��������Ȃ�";
		mes "�����ӑĂɉ߂����Ă܂��B";
		next;
		mes "[�W���W��]";
		mes "�������c�c";
		mes "��l�ł����Ƙb��������";
		mes "���݂��̌�����������";
		mes "�v���̂ł����c�c�b�͂��܂������H";
		next;
		mes "[�h���L����]";
		mes "�ڊo�߂��{�~�͓{��A�߂��񂾁B";
		mes "����������������";
		mes "�{�~�͕�������Ȃ������B";
		next;
		mes "[�h���L����]";
		mes "�{�~�̂��߂ɂ�������Ƃ����A";
		mes "�{�~�͖]��ł��Ȃ��������Ƃ��B";
		mes "���ւ̓{��Ɣ߂��݂�";
		mes "������O�̂��Ƃ��B";
		next;
		mes "[�L���O]";
		mes "�h���L�����A����Ȑl�Ԃ��ǂ������I";
		mes "���܂ł���ȂƂ����";
		mes "�����Ă��Ă������Ȃ񂾁H";
		mes "����Ȃ��Ƃ��������āA";
		mes "�N�����O��F�߂Ă���Ȃ����B";
		next;
		mes "[�h���L����]";
		mes "����́A�����c�c";
		next;
		emotion 0,"�L���O#ilgf01";
		mes "[�L���O]";
		mes "�c�c�I";
		next;
		mes "[�L���O]";
		mes "������Ɓc�c�҂āB";
		mes "���������B�������B";
		chgquest 14661,14662;
		set IL_VAMP_QUE,11;
		close;
	case 11:
		mes "[�h���L����]";
		mes "�L���O�H�@�����Ƃ��H";
		close;
	case 12:
	case 13:
		mes "[�h���L����]";
		mes "�����A�܂����c�c�I";
		close2;
		viewpoint 1, 85, 131, 1, 0x00FF00;
		end;
	case 14:
	case 15:
		mes "[�h���L����]";
		mes "�����x�݂Ȃ���";
		mes "�{�~��҂Ƃ��悤�B";
		close;
	}
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,185,97,5	script	�L���O#ilgf01	799,{
	if(IL_VAMP_QUE <= 10) {
		mes "[�L���O]";
		mes "�����p������H";
		mes "�Ȃ���Ύ�����I";
		close;
	}
	else if(IL_VAMP_QUE == 11) {
		mes "[�L���O]";
		mes "^0000cd���̓���^000000������I";
		mes "�l�Ԃ̌��̓������I";
		next;
		mes "[�W���W��]";
		mes "��A�����Ⴀ��܂����I";
		mes "����͑S����������ł���I";
		next;
		mes "[�L���O]";
		mes "����A����͕��̂ǂ�������";
		mes "�Y���Ă��Ă���������B";
		mes "����́c�c^0000cd����^000000�I�@�������I";
		mes "�s���Ă݂悤�I";
		next;
		menu "�܂�������̐l�������c�c�B",-;
		mes "[�h���L����]";
		mes "����H";
		next;
		emotion 27,"�L���O#ilgf01";
		mes "[�L���O]";
		mes "���񂭂�I";
		mes "���������I";
		mes "�k�̕�����������I";
		chgquest 14662,14663;
		set IL_VAMP_QUE,12;
		close2;
		viewpoint 1, 85, 131, 1, 0x00FF00;
		end;
	}
	else if(IL_VAMP_QUE == 12 || IL_VAMP_QUE == 13) {
		mes "[�L���O]";
		mes "���񂭂�I";
		mes "���������I";
		mes "����������������I";
		close2;
		viewpoint 1, 85, 131, 1, 0x00FF00;
		end;
	}
	mes "[�L���O]";
	mes "�Ȃ񂾁H";
	mes "�h���L�����ɂ͋x�����K�v�Ȃ񂾁B";
	mes "�ז�����Ȃ�B";
	close;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,191,96,3	script	���@�g��#ilgf02	735,{
	if(IL_VAMP_QUE <= 10) {
		mes "[�W���W��]";
		mes "�����c�c���͎������̂ɁA";
		mes "�Ȃ�ł���Ȃɒɂ��́B";
		close;
	}
	else if(IL_VAMP_QUE == 11) {
		mes "[�W���W��]";
		mes "�L���O���񂪉����̓�����";
		mes "�C�Â����悤�ł��B";
		mes "����������f�r���Ă�������";
		mes "�ނ������ɋC�Â��Ă��ꂽ";
		mes "�炵���ł��B";
		close;
	}
	else if(IL_VAMP_QUE == 12 || IL_VAMP_QUE == 13) {
		mes "[�W���W��]";
		mes "�������ő�����";
		mes "�N���Ă���݂����ł��ˁB";
		mes "�����s���Ă݂܂��傤�B";
		close2;
		viewpoint 1, 85, 131, 1, 0x00FF00;
		end;
	}
	mes "[�W���W��]";
	mes "���͓����̊ԁA";
	mes "������Ɏc�����ł��B";
	mes "�h���L�������񂪉񕜂���܂�";
	mes "�����������Ԃ������肻���ł��B";
	next;
	mes "[�W���W��]";
	mes "�V�X�^�[�W�F����s��";
	mes "���W���ɂ����`���Ă��������B";
	close;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,80,139,5	script	�W�F��#ilgf02	79,{
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,86,133,1	script	�}���i#ilgf02	746,5,5,{
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,85,139,3	script	�A���g���[�k#ilgf02	669,{
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,84,135,3	script	�h���L����#ilgf03	10137,{
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,87,137,3	script	�L���O#ilgf02	799,{
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,80,132,7	script	�W���W��#ilgf01	735,{
	end;
OnInit:
	cloakonnpc;
	end;
}

gef_d01_i.gat,114,216,0	script	#ilgf01	139,3,0,{
	misceffect 561,"";
	if(IL_VAMP_QUE == 6) {
		cloakonnpc "���@�g��#ilgf01";
		cloakoffnpc "�i��#ilgf01";
		cloakoffnpc "�}���i#ilgf03";
		cloakoffnpc "�}���i#ilgf04";
		cloakoffnpc "�}���i#ilgf05";
		cloakoffnpc "�}���i#ilgf06";
		cloakoffnpc "�}���i#ilgf07";
		cloakoffnpc "�}���i#ilgf08";
		cloakoffnpc "�}���i#ilgf09";
	}
	else if(IL_VAMP_QUE == 7) {
		cloakoffnpc "���@�g��#ilgf01";
		cloakonnpc "�}���i#ilgf07";
		cloakonnpc "�i��#ilgf01";
		cloakoffnpc "���@�g��#ilgf25";
		cloakoffnpc "���@�g��#ilgf26";
		cloakoffnpc "�A���f�b�h#ilgf01";
		cloakoffnpc "���@�g��#ilgf24";
		cloakoffnpc "����L�m�R#ilgf01";
		cloakoffnpc "���@�g��#ilgf23";
		cloakoffnpc "�����A���f�b�h#ilgf01";
		cloakoffnpc "���@�g��#ilgf21";
		cloakoffnpc "���@�g��#ilgf22";
		cloakoffnpc "�A���f�b�h#ilgf02";
		cloakoffnpc "�A���f�b�h#ilgf03";
		cloakoffnpc "�A���f�b�h#ilgf04";
		cloakoffnpc "���@�g��#ilgf19";
		cloakoffnpc "���@�g��#ilgf20";
		cloakoffnpc "�A���f�b�h#ilgf05";
		cloakoffnpc "���@�g��#ilgf18";
		cloakoffnpc "�N���̖�#ilgf18";
		cloakoffnpc "���@�g��#ilgf16";
		cloakoffnpc "���@�g��#ilgf17";
		cloakoffnpc "���@�g��#ilgf14";
		cloakoffnpc "���@�g��#ilgf15";
		cloakoffnpc "����������#ilgf01";
		cloakoffnpc "���@�g��#ilgf12";
		cloakoffnpc "���@�g��#ilgf13";
		cloakoffnpc "����������#ilgf02";
		cloakoffnpc "���@�g��#ilgf11";
		cloakoffnpc "���@�g��#ilgf09";
		cloakoffnpc "���@�g��#ilgf10";
		cloakoffnpc "���@�g��#ilgf08";
		cloakoffnpc "����������#ilgf03";
		cloakoffnpc "���@�g��#ilgf06";
		cloakoffnpc "���@�g��#ilgf07";
		cloakoffnpc "�A���f�b�h#ilgf06";
		cloakoffnpc "���@�g��#ilgf27";
		cloakoffnpc "���@�g��#ilgf28";
	}
	else if(IL_VAMP_QUE == 8 || IL_VAMP_QUE == 9) {
		cloakoffnpc "���@�g��#ilgf01";
		cloakonnpc "�h���L����#ilgf03";
		cloakonnpc "�L���O#ilgf02";
		cloakonnpc "�W���W��#ilgf01";
		cloakonnpc "�W�F��#ilgf02";
		cloakonnpc "�}���i#ilgf02";
		cloakonnpc "�A���g���[�k#ilgf02";
	}
	end;
}

gef_d01_i.gat,96,135,0	script	#illcon01	139,5,7,{
	if(IL_VAMP_QUE < 7) {
		cloakonnpc "���@�g��#ilgf01";
		cloakonnpc "�h���L����#ilgf03";
		cloakonnpc "�L���O#ilgf02";
		cloakonnpc "�W���W��#ilgf01";
		cloakonnpc "�W�F��#ilgf02";
		cloakonnpc "�}���i#ilgf02";
		cloakonnpc "�A���g���[�k#ilgf02";
	}
	else if(IL_VAMP_QUE < 12 || IL_VAMP_QUE >= 14) {
		cloakoffnpc "���@�g��#ilgf01";
		cloakonnpc "�h���L����#ilgf03";
		cloakonnpc "�L���O#ilgf02";
		cloakonnpc "�W���W��#ilgf01";
		cloakonnpc "�W�F��#ilgf02";
		cloakonnpc "�}���i#ilgf02";
		cloakonnpc "�A���g���[�k#ilgf02";
	}
	else if(IL_VAMP_QUE == 12) {
		cloakoffnpc "���@�g��#ilgf01";
		cloakoffnpc "�W�F��#ilgf02";
		cloakoffnpc "�}���i#ilgf02";
		cloakoffnpc "�A���g���[�k#ilgf02";
		cloakonnpc "�h���L����#ilgf03";
		cloakonnpc "�L���O#ilgf02";
		cloakonnpc "�W���W��#ilgf01";
	}
	else if(IL_VAMP_QUE == 13) {
		cloakoffnpc "���@�g��#ilgf01";
		cloakoffnpc "�W�F��#ilgf02";
		cloakoffnpc "�}���i#ilgf02";
		cloakoffnpc "�A���g���[�k#ilgf02";
		cloakoffnpc "�h���L����#ilgf03";
		cloakoffnpc "�L���O#ilgf02";
		cloakoffnpc "�W���W��#ilgf01";
	}
	end;
}
gef_d01_i.gat,81,135,0	duplicate(#illcon01)	#illcon02	139,5,7
gef_d01_i.gat,81,120,0	duplicate(#illcon01)	#illcon03	139,5,7
gef_d01_i.gat,96,120,0	duplicate(#illcon01)	#illcon04	139,5,7

gef_d01_i.gat,174,83,0	script	#illcon05	139,5,7,{
	if(IL_VAMP_QUE < 9) {
		cloakonnpc "���@�g��#ilgf02";
		cloakonnpc "�L���O#ilgf01";
		cloakonnpc "�h���L����#ilgf02";
		end;
	}
	cloakoffnpc "�h���L����#ilgf02";
	cloakoffnpc "�L���O#ilgf01";
	cloakoffnpc "���@�g��#ilgf02";
	end;
}
gef_d01_i.gat,189,98,0	duplicate(#illcon05)	#illcon06	139,5,7
gef_d01_i.gat,189,83,0	duplicate(#illcon05)	#illcon07	139,5,7
gef_d01_i.gat,204,83,0	duplicate(#illcon05)	#illcon08	139,5,7
gef_d01_i.gat,174,98,0	duplicate(#illcon05)	#illcon09	139,5,7
gef_d01_i.gat,204,98,0	duplicate(#illcon05)	#illcon10	139,5,7
gef_d01_i.gat,174,113,0	duplicate(#illcon05)	#illcon11	139,5,7
gef_d01_i.gat,189,113,0	duplicate(#illcon05)	#illcon12	139,5,7
gef_d01_i.gat,204,113,0	duplicate(#illcon05)	#illcon13	139,5,7

//==============================================================================

gef_d01_i.gat,49,113,3	script	���@�g��#ilgf06	669,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	misceffect 1033,"�A���f�b�h#ilgf06";
	if(!sleep2(1000)) end;
	hideonnpc "�A���f�b�h#ilgf06";
	unittalk getnpcid(0,"���@�g��#ilgf06"),"���@�g�� : �����I�@���ł��Ă��܂����I";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf07"),"���@�g�� : �A���f�b�h������A�C�O�h���V���̗t�̌��ʂ��t�ɍ�p�����񂶂�Ȃ��H";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf06"),"���@�g�� : �����݂����ˁB���ꂩ��̓A���f�b�h�ɉ������C�O�h���V���̗t���g���΂����񂶂�Ȃ��H";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf07"),"���@�g�� : �V�˂��I";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : ����́c�c�m�[�g�̎�����̌Â��L���̂悤���B",1;
	if(!sleep2(1000)) end;
	cloakonnpc "���@�g��#ilgf06";
	cloakonnpc "���@�g��#ilgf07";
	cloakonnpc "�A���f�b�h#ilgf06";
	misceffect 496,"���@�g��#ilgf06";
	misceffect 496,"���@�g��#ilgf07";
	misceffect 496,"�A���f�b�h#ilgf06";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,46,112,5	script	���@�g��#ilgf07	937,{
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,47,110,7	script	�A���f�b�h#ilgf06	1036,{
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_i.gat,137,60,3	script	���@�g��#ilgf08	64,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	misceffect 611,"����������#ilgf03";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf08"),"���@�g�� : ����A����ł��N���オ��Ȃ��ȁB�ǂ�����ēz��͓�������Ă�񂾂�H";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : ����́c�c�m�[�g�̎�����̌Â��L���̂悤���B",1;
	if(!sleep2(1000)) end;
	cloakonnpc "���@�g��#ilgf08";
	cloakonnpc "����������#ilgf03";
	misceffect 496,"���@�g��#ilgf08";
	misceffect 496,"����������#ilgf03";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,136,58,5	script	����������#ilgf03	557,{
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_i.gat,67,85,5	script	���@�g��#ilgf09	735,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	unittalk getnpcid(0,"���@�g��#ilgf09"),"���@�g�� : ���̃W�F���X�g�[�����ӂ��č����Ďg�p����΁A���̓��̂ƍ����q���}�̂𕪗��ł���񂶂�Ȃ����낤���H";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf10"),"���@�g�� : ���̌����ł́A���̃]���r�����ɂ͍��������Ă���Ƃ݂��B";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf09"),"���@�g�� : �Ȃ炢�������ǂ�����ē����Ă���H�@�����鐶���ɂ͍����h���Ă�񂾂�I";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf10"),"���@�g�� : �ؓ��̔����H";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf09"),"���@�g�� : ����͂ǂ����Ă����񂾑̂ɍ����߂��Ă���I�@�̂��獰�����R�ɒE���ł���΁A�������͓��̂̂����炷��ɂ��玩�R�ɂȂ��I";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf10"),"���@�g�� : �ǂ������c�c���������Ă��̂��������Ă邩���m��Ȃ��B����͂ǂ��݂Ă��c�c�B";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf09"),"���@�g�� : �ׂ��׌��킸�ɁA����������ӂ��āB";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : ����́c�c�m�[�g�̎�����̌Â��L���̂悤���B",1;
	if(!sleep2(1000)) end;
	cloakonnpc "���@�g��#ilgf09";
	cloakonnpc "���@�g��#ilgf10";
	misceffect 496,"���@�g��#ilgf09";
	misceffect 496,"���@�g��#ilgf10";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,67,83,1	script	���@�g��#ilgf10	673,{
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_i.gat,156,234,3	script	���@�g��#ilgf11	567,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	unittalk getnpcid(0,"���@�g��#ilgf11"),"���@�g�� : �n���[�I�@�`���ҁH�@���΁H�@�����͏��߂āH";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : ���̃m�[�r�X������ȏꏊ�Ɂc�c�H",1;
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf11"),"���@�g�� : �����m�[�r�X�Ɍ�����H�@���킢���ˁB";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : ����́c�c�����낤�H",1;
	if(!sleep2(1000)) end;
	cloakonnpc "���@�g��#ilgf11";
	misceffect 496,"���@�g��#ilgf11";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_i.gat,48,255,5	script	���@�g��#ilgf12	64,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	unittalk getnpcid(0,"���@�g��#ilgf12"),"���@�g�� : 48��ڂ̎����B�����A���x�͐����������Ă݂܂��B";
	if(!sleep2(1500)) end;
	misceffect 628,"����������#ilgf02";
	emotion 9,"����������#ilgf02";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf12"),"���@�g�� : ���̕ω�������܂���ł����B�����̗ʂ𑝂₵49��ڂ̎������n�߂܂��B";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf13"),"���@�g�� : ���E�҂��Ă񂾕����悭�Ȃ��H";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf12"),"���@�g�� : �����܂���B���E�҂����͂�����������r�[�A�������Ƃ���ł��傤�B�L�^�ɏW�����āB";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : ����́c�c�m�[�g�̎�����̌Â��L���̂悤���B",1;
	if(!sleep2(1000)) end;
	cloakonnpc "���@�g��#ilgf12";
	cloakonnpc "���@�g��#ilgf13";
	cloakonnpc "����������#ilgf02";
	misceffect 496,"���@�g��#ilgf12";
	misceffect 496,"���@�g��#ilgf13";
	misceffect 496,"����������#ilgf02";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,50,257,5	script	���@�g��#ilgf13	123,{
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,50,254,5	script	����������#ilgf02	557,{
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_i.gat,112,267,3	script	���@�g��#ilgf14	735,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	unittalk getnpcid(0,"���@�g��#ilgf14"),"���@�g�� : �N���オ��I";
	if(!sleep2(1500)) end;
	misceffect 348,"����������#ilgf01";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf14"),"���@�g�� : �_���������B";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf15"),"���@�g�� : ����������Ȃ��B�����ԍ��̂��D��457�����g���Ă݂����ǃ_�����������āB���������z��͈Ⴄ�����œ����Ă�񂾂�B";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf14"),"���@�g�� : ���̌����Ƃ͉��H";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf15"),"���@�g�� : �����m�邩�B";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : ����́c�c�m�[�g�̎�����̌Â��L���̂悤���B",1;
	if(!sleep2(1000)) end;
	cloakonnpc "���@�g��#ilgf14";
	cloakonnpc "���@�g��#ilgf15";
	cloakonnpc "����������#ilgf01";
	misceffect 496,"���@�g��#ilgf14";
	misceffect 496,"���@�g��#ilgf15";
	misceffect 496,"����������#ilgf01";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,110,266,5	script	���@�g��#ilgf15	937,{
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,111,264,5	script	����������#ilgf01	557,{
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_i.gat,55,167,3	script	���@�g��#ilgf16	937,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	unittalk getnpcid(0,"���@�g��#ilgf16"),"���@�g�� : �|�s�ɉ�����B����ɐ���������A�^����Ƀ|�s���Ăт����B";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf17"),"���@�g�� : ��߂�B���������Ɩ����ɖ߂ꂻ���ɂ��Ȃ��B���̑���ɂ��񂽂̑��̍������ނ�B";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : ����́c�c�m�[�g�̎�����̌Â��L���̂悤���B",1;
	if(!sleep2(1000)) end;
	cloakonnpc "���@�g��#ilgf16";
	cloakonnpc "���@�g��#ilgf17";
	misceffect 496,"���@�g��#ilgf16";
	misceffect 496,"���@�g��#ilgf17";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,53,166,7	script	���@�g��#ilgf17	123,{
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_i.gat,236,235,1	script	���@�g��#ilgf18	64,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	unittalk getnpcid(0,"�N���̖�#ilgf18"),"�N���̖� : �q�q�[���I";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf18"),"���@�g�� : �����I�@���߂�Ȃ����I�@���Ȃ��������閲�͋C������������B";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : ����́c�c�m�[�g�̎�����̌Â��L���̂悤���B",1;
	if(!sleep2(1000)) end;
	cloakonnpc "���@�g��#ilgf18";
	cloakonnpc "�N���̖�#ilgf18";
	misceffect 496,"���@�g��#ilgf18";
	misceffect 496,"�N���̖�#ilgf18";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,233,237,5	script	�N���̖�#ilgf18	1061,{
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_i.gat,255,201,5	script	���@�g��#ilgf19	673,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	misceffect 315,"���@�g��#ilgf19";
	misceffect 315,"���@�g��#ilgf20";
	unittalk getnpcid(0,"���@�g��#ilgf19"),"���@�g�� : ���c�c�ǂ����悤�c�c�v������苭���B";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf20"),"���@�g�� : �������A���A���́H";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf19"),"���@�g�� : ���ꂪ�s���܂ł̓_���B���o����E�����c�c�B";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : ����́c�c�m�[�g�̎�����̌Â��L���̂悤���B",1;
	if(!sleep2(1000)) end;
	cloakonnpc "���@�g��#ilgf19";
	cloakonnpc "���@�g��#ilgf20";
	cloakonnpc "�A���f�b�h#ilgf05";
	misceffect 496,"���@�g��#ilgf19";
	misceffect 496,"���@�g��#ilgf20";
	misceffect 496,"�A���f�b�h#ilgf05";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,254,200,5	script	���@�g��#ilgf20	123,{
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,256,198,1	script	�A���f�b�h#ilgf05	1036,{
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_i.gat,204,146,1	script	���@�g��#ilgf21	673,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	emotion 23,"���@�g��#ilgf21";
	unittalk getnpcid(0,"���@�g��#ilgf21"),"���@�g�� : �����I�@���߂��邶��Ȃ����I�@��C�����A��ė��Ăƌ������̂ɁA����ȂɘA��ė��Ăǂ�����I";
	if(!sleep2(1500)) end;
	emotion 26,"���@�g��#ilgf22";
	unittalk getnpcid(0,"���@�g��#ilgf22"),"���@�g�� : ���傤���Ȃ�����I�@���̊Ԃɂ�������������񂾂���I";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf21"),"���@�g�� : ���������āI";
	if(!sleep2(1500)) end;
	misceffect 97,"�A���f�b�h#ilgf02";
	misceffect 97,"�A���f�b�h#ilgf03";
	misceffect 97,"�A���f�b�h#ilgf04";
	if(!sleep2(1500)) end;
	cloakonnpc "�A���f�b�h#ilgf02";
	cloakonnpc "�A���f�b�h#ilgf03";
	cloakonnpc "�A���f�b�h#ilgf04";
	unittalk getnpcid(0,"���@�g��#ilgf22"),"���@�g�� : �ӂ��c�c���������B";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : ����́c�c�m�[�g�̎�����̌Â��L���̂悤���B",1;
	if(!sleep2(1000)) end;
	cloakonnpc "���@�g��#ilgf21";
	cloakonnpc "���@�g��#ilgf22";
	misceffect 496,"���@�g��#ilgf21";
	misceffect 496,"���@�g��#ilgf22";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,202,149,5	script	���@�g��#ilgf22	937,{
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,202,152,5	script	�A���f�b�h#ilgf02	1036,{
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,200,151,5	script	�A���f�b�h#ilgf03	1015,{
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,204,151,3	script	�A���f�b�h#ilgf04	1036,{
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_i.gat,257,110,1	script	���@�g��#ilgf23	10224,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	unittalk getnpcid(0,"���@�g��#ilgf23"),"���@�g�� : ������A�Ȃ�ł���Ȃɑ��������́H�@���ׂ�O�Ɏ������̐��ɍs�����Ⴄ��B";
	if(!sleep2(1500)) end;
	misceffect 95,"�����A���f�b�h#ilgf01";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf23"),"���@�g�� : ����Ȃ̂��ǂ�����ĕ߂܂���́c�c�B�������ɘA��Ă��������̂Ɂc�c�B";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : ����́c�c�m�[�g�̎�����̌Â��L���̂悤���B",1;
	if(!sleep2(1000)) end;
	cloakonnpc "���@�g��#ilgf23";
	cloakonnpc "�����A���f�b�h#ilgf01";
	misceffect 496,"���@�g��#ilgf23";
	misceffect 496,"�����A���f�b�h#ilgf01";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,253,112,5	script	�����A���f�b�h#ilgf01	1036,{
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_i.gat,230,76,3	script	���@�g��#ilgf24	704,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	unittalk getnpcid(0,"���@�g��#ilgf24"),"���@�g�� : �悵�悵�c�c�E�q�̏W���Ɏ��ʖ�ɂ͂�����B";
	if(!sleep2(1500)) end;
	misceffect 543,"����L�m�R#ilgf01";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf24"),"���@�g�� : ���ꂮ�炢����΁A�����������̌��ŏ���邩�ȁH";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : ����́c�c�m�[�g�̎�����̌Â��L���̂悤���B",1;
	if(!sleep2(1000)) end;
	cloakonnpc "���@�g��#ilgf24";
	cloakonnpc "����L�m�R#ilgf01";
	misceffect 496,"���@�g��#ilgf24";
	misceffect 496,"����L�m�R#ilgf01";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,228,75,3	script	����L�m�R#ilgf01	3755,{
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_i.gat,93,34,1	script	���@�g��#ilgf25	10224,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	unittalk getnpcid(0,"���@�g��#ilgf25"),"���@�g�� : ���x�̓X�N���[���ƃC�O�h���V���̗t���ꏏ�Ɏg���Ă݂悤�B�����X�N���[�����g������A���񂽂̓C�O�h���V���̗t���g���āB";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf26"),"���@�g�� : �����B";
	if(!sleep2(1500)) end;
	misceffect 53,"�A���f�b�h#ilgf01";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf25"),"���@�g�� : ��������s�H";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf26"),"���@�g�� : �Ȃ�ŏ�肭�����Ȃ��́H�@���_��͂���Ől�ԂɂȂ�͂�����H";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf25"),"���@�g�� : ���������āB���͈Ⴄ���@�ł���Ă݂悤�B";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : ����́c�c�m�[�g�̎�����̌Â��L���̂悤���B",1;
	if(!sleep2(1000)) end;
	cloakonnpc "���@�g��#ilgf25";
	cloakonnpc "���@�g��#ilgf26";
	cloakonnpc "�A���f�b�h#ilgf01";
	misceffect 496,"���@�g��#ilgf25";
	misceffect 496,"���@�g��#ilgf26";
	misceffect 496,"�A���f�b�h#ilgf01";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,94,37,3	script	���@�g��#ilgf26	64,{
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,91,35,5	script	�A���f�b�h#ilgf01	1036,{
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_i.gat,101,124,3	script	���@�g��#ilgf27	10224,5,5,{
	end;
OnTouch:
	if(IL_VAMP_QUE != 7) end;
	pcblockmove 1;
	unittalk getnpcid(0,"���@�g��#ilgf27"),"���@�g�� : ����ȂƂ���ŉ��̎���������́H�@�߂��Ď����A������H";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf28"),"���@�g�� : �����ɗ����C�z��������H";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf27"),"���@�g�� : ���ꂪ�����H";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf28"),"���@�g�� : ���̗͂������������p�ł���Ǝv��Ȃ��H";
	if(!sleep2(1500)) end;
	unittalk getnpcid(0,"���@�g��#ilgf27"),"���@�g�� : ���[��c�c�B";
	if(!sleep2(1500)) end;
	unittalk getcharid(3),strcharinfo(0)+" : ����́c�c�m�[�g�̎�����̌Â��L���̂悤���B",1;
	if(!sleep2(1000)) end;
	cloakonnpc "���@�g��#ilgf27";
	cloakonnpc "���@�g��#ilgf28";
	misceffect 496,"���@�g��#ilgf27";
	misceffect 496,"���@�g��#ilgf28";
	pcblockmove 0;
	end;
OnInit:
	cloakonnpc;
	end;
}
gef_d01_i.gat,99,122,7	script	���@�g��#ilgf28	10224,{
	end;
OnInit:
	cloakonnpc;
	end;
}

//==============================================================================

gef_d01_j.gat,81,135,5	script	�{�~#gef_d01_j	10224,{
	if('spawn)
		set '@name$,"[�{�~�̎莆]";
	else
		set '@name$,"[�{�~]";
	if(checkquest(14674)) {
		if(checkquest(14674) & 0x2) {
			mes '@name$;
			mes "�`���җl�A";
			mes "����͂��肪�Ƃ��������܂����B";
			mes "��낵����΂܂�����";
			mes "���ޗ�������Ă��Ă��������B";
			mes "���Ȃ�����������ł��B";
			mes "��낵�����肢���܂��B";
			delquest 14674;
			setquest 14671;
			close;
		}
		mes '@name$;
		mes "�`���җl�A";
		mes "����͂��肪�Ƃ��������܂����B";
		mes "���͌�������Ă���̂�";
		mes "�܂���ŗ��Ă��������܂����H";
		close;
	}
	if(checkquest(14671)) {
		if(checkquest(14671) & 0x4 == 0 || countitem(25268) < 10 || countitem(25269) < 10) {
			mes '@name$;
			mes "�`���җl�A";
			mes "���𗊂܂ꂽ�̂��Y�ꂽ�悤�ł��ˁB";
			next;
			mes '@name$;
			mes "^0000cd�}�b�g�h���C�����A�[��";
			mes "�u���̂���5�̈ȏ����āA";
			mes "�ׂƂׂƂ��錌��";
			mes "���̂��̔S�t��10��^000000";
			mes "�K�v�ł��B���肢���܂��B";
			close;
		}
		if(checkitemblank() == 0) {
			mes "�]�����A�C�e���̎�ސ���������";
			mes "�@�댯�ł��B";
			mes "�@�����A�C�e�������炵�Ă���A";
			mes "�@�ēx�b�������Ă��������]";
			close;
		}
		mes '@name$;
		mes "�`���җl�A";
		mes "�����Ă���āA�{���ɂ��肪�Ƃ��B";
		delitem 25268,10;
		delitem 25269,10;
		chgquest 14671,14674;
		getexp 100000000,0,1;
		getexp 0,20000000,0;
		getitem 25271,2;
		$IllVampBomiQuest++;
		close;
	}
	mes '@name$;
	mes "�`���җl�A";
	mes "�������Ԃ�����Ȃ�A";
	mes "���̗��݂𕷂��Ă���܂��񂩁H";
	next;
	if(select("�������ł��B","���͂�����ƖZ�����ł��ˁB") == 2) {
		mes '@name$;
		mes "�����ł����c�c";
		mes "�d������܂���ˁB";
		close;
	}
	mes '@name$;
	mes "�����U���̌��Ő����Ă�̂́A";
	mes "�������ł���ˁB";
	mes "����܂ł͎��̕������\���ł������A";
	mes "���ꂩ��h���L�����̕���";
	mes "����Ă����悤�Ǝv���܂��B";
	next;
	mes '@name$;
	mes "^0000cd�}�b�g�h���C�����A�[��";
	mes "�u���̂���5�̈ȏ����āA";
	mes "�ׂƂׂƂ��錌��";
	mes "���̂��̔S�t��10��^000000";
	mes "�W�߂Ă��Ă͂���Ȃ��ł��傤���B";
	next;
	mes '@name$;
	mes "���������C������Ȃ̂́A";
	mes "�U���̌��ɂ͂ǂ����Ă��őf��";
	mes "�c���Ă��܂��̂ŁA";
	mes "���݂�����Ɠőf�����܂�A";
	mes "�ꎞ�I�ɗ����������Ă��܂��̂ł��B";
	next;
	mes '@name$;
	mes "���܂ł͓ł�������܂�";
	mes "�҂��Ă���΂悩�����̂ł����A";
	mes "���͎��ȊO�̐l�Ԃ�";
	mes "�����ɂ���̂Łc�c";
	next;
	mes '@name$;
	mes "�Ȃ̂ł���������������������A";
	mes "���̐l���Q���Ȃ��悤�A";
	mes "�`���җl���~�߂Ă��������B";
	mes "�ȂɂƂ����肢���܂��B";
	next;
	mes '@name$;
	mes "���͂��̑̂ɂȂ��Ă���";
	mes "�܂����Ԃ����܂�o���Ă��Ȃ��̂�";
	mes "�ϐ����ア���炩���m��܂���B";
	mes "�h���L�����͉i�������Ă��邵�A";
	mes "����������v�ł��傤�B";
	setquest 14671;
	close;
OnSpawn:
	setnpcdisplay "�{�~#gef_d01_j",801;
	set 'spawn,1;
	end;
OnReflesh:
	setnpcdisplay "�{�~#gef_d01_j",10224;
	set 'spawn,0;
	end;
}

gef_d01_j.gat,189,98,3	script	�h���L����#gef_d01_j	10137,{
	mes "[�h���L����]";
	mes "�{�~���R�E�����̌������񂾌�A";
	mes "���X�ꂵ�݂Ȃ���\��鎞������B";
	mes "���Ԃ��o�ĂΗ��������̂����A";
	mes "����ċ���̐l�Ԃ�����";
	mes "�P���ł�������c�c�B";
	close;
}

gef_d01_j.gat,113,230,5	script	�W�F��#gef_d01_j	79,{
	mes "[�W�F��]";
	mes "�������C�z�̂���ꏊ�ł��B";
	mes "�C���������莝���Ă��������B";
	close;
}

gef_d01_j.gat,112,228,5	script	�}���i#gef_d01_j	746,{
	mes "[�}���i]";
	mes "���̏ꏊ�ɖ߂�܂����H";
	next;
	if(select("�͂�","������") == 2) {
		mes "[�}���i]";
		mes "�킩��܂����B";
		mes "�߂鎞�͂��ł�";
		mes "���������Ă��������B";
		close;
	}
	mes "[�}���i]";
	mes "�����ɂ����ӂ��������B";
	close2;
	warp "gef_dun01.gat", 133, 219;
	end;
}

gef_d01_j.gat,116,228,3	script	�A���g���[�k#gef_d01_j	669,{
	mes "[�A���g���[�k]";
	mes "�����͋����[���������߂���";
	mes "��������������ǂ���";
	mes "�Y�܂����ł��ˁB";
	close;
}

gef_d01_j.gat,185,97,5	script	�L���O#gef_d01_j	799,{
	mes "[�L���O]";
	mes "�����قƂ�ǎ����Ă���̂�";
	mes "��������o�悤�Ƃ��Ȃ��B";
	mes "��̂��̐l�Ԃ̉�������Ȃ�";
	mes "�C�ɓ������񂾂��B";
	next;
	mes "[�L���O]";
	mes "���������΂��O�A";
	mes "���ł܂������ɂ���񂾁H";
	mes "�h���L�����͂قڊ����������H";
	next;
	mes "[�W���W��]";
	mes "�����ɂ͒��ׂ������̂�";
	mes "�������񂠂��ł���B";
	next;
	mes "[�W���W��]";
	mes "����ɁA";
	mes "�h���L���������L���O�����";
	mes "�ꏏ�ɋ���Έ��S�ł����B";
	next;
	emotion 4,"�L���O#gef_d01_j";
	mes "[�L���O]";
	mes "���O�ȁc�c�B";
	close;
}

gef_d01_j.gat,191,96,3	script	�W���W��#gef_d02_j	735,{
	mes "[�W���W��]";
	mes "���W���͌��C�����ł������H";
	mes "�����͍D��S�̉򂾂���A";
	mes "�O�����i�Ղ͋�J�������ł��ˁB";
	close;
}

gef_d01_j.gat,0,0,0	script	#IllVampire	-1,{
OnInit:
	setarray 'table,3750,3752,3753,3754;
	for(set '@i,0;'@i<6;set '@i,'@i+1)
		areamonster "gef_d01_j.gat",40,35,250,250,"--ja--",'table[rand(4)],1,strnpcinfo(0)+"::OnSummon";
	end;
OnSummon:
	if('mob == 0 && $IllVampBomiQuest >= 3 && rand(250) < $IllVampBomiQuest*2) {
		initnpctimer;
	}
	areamonster "gef_d01_j.gat",40,35,250,250,"--ja--",'table[rand(4)],1,strnpcinfo(0)+"::OnSummon";
	end;
OnTimer15000:
	stopnpctimer;
	set '@x,rand(40,250);
	set '@y,rand(40,250);
	//set 'mob,callmonster("gef_d01_j.gat",'@x,'@y,"�{�~",3756,strnpcinfo(0)+"::OnBomiKilled");
	set 'mob,areacallmonster("gef_d01_j.gat",0,0,0,0,"�{�~",3756,strnpcinfo(0)+"::OnBomiKilled");
	unittalk 'mob,"�{�~ : �`�c�c���c�c�ҁc�c���܁c�c�����c�c�āc�c";
//	mobuseskillpos 'mob,21,10,210,221,0,0;	// �T���_�[�X�g�[��
//	mobuseskill 'mob,730,1,0,0,0,1;	// M�����w
	announce "�{�~ : �_�A�_���c�c�ł����n�߂āc�c�I", 0x9, 0xee0000, 0x0190, 20, 0, 0;
	donpcevent "�{�~#gef_d01_j::OnSpawn";
	end;
OnBomiKilled:
	startnpctimer;
	end;
OnTimer75000:
	announce "�]�{�~����������ɗ����܂����]", 0x9, 0x00ebff, 0x0190, 20, 0, 0;
	end;
OnTimer135000:
	announce "�{��̃h���L���� : �{�~�����t����̂͒N���I", 0x9, 0xee0000, 0x0190, 20, 0, 0;
	end;
OnTimer195000:
	stopnpctimer;
	announce "�{��̃h���L���� : ����ȏ�{�~�Ɏ���o���ȁI�@�ǂ����Ă��ƌ����Ȃ����ɉ�����������Ă��B", 0x9, 0xee0000, 0x0190, 20, 0, 0;
	hideonnpc "�h���L����#gef_d01_j";
	areamonster "gef_d01_j.gat",40,35,250,250,"�{��̃h���L����",3757,1,strnpcinfo(0)+"::OnDracKilled";
	end;
OnDracKilled:
	startnpctimer;
	end;
OnTimer245000:
	stopnpctimer;
	hideoffnpc "�h���L����#gef_d01_j";
	announce "�{��̃h���L���� : �܂��Ȃ��{�~���ڊo�߂�B�l�ԒB��A�񑩂�Y���ȁI", 0x9, 0x00ff00, 0x0190, 20, 0, 0;
	donpcevent "�{�~#gef_d01_j::OnReflesh";
	set 'mob,0;
	set $IllVampBomiQuest,0;
	areamonster "gef_d01_j.gat",40,35,250,250,"--ja--",'table[rand(4)],1,strnpcinfo(0)+"::OnSummon";
	end;
}