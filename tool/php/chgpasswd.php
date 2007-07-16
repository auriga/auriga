<?php
// With this code, you have a HTML page to change password of player
// *****************************************************************

// note: player must confirm old password, and its e-mail if you want better protection (default)
//       This php need only 'class ladmin' included in 'auriga.php'.

// By Yor (alias DarkRaven)

	// -------------------
	// ---- Options (please modify desired values):
	$Language = 'Japanese'; // possible: 'Japanese' (default), 'English', 'French', 'Russian'
	$css_style = '<your style.css url>'; // Set here the link to add a style (used in <link rel="stylesheet" href="MylCastel.css" type="text/css">)
	$CheckEmail = 1; // 0: doesn't check email of account, 1: Check Email of account (default)
	$serverip = '127.0.0.1'; // Set here ip of the login server (default: 127.0.0.1)
	$serverport = 6900; // Set here port of your login-server (default: 6900)
	$adminpasswd = 'admin'; // Set here ladmin password of your server
	// ---- End of options
	// -------------------

	// Texts of each language
	// ----------------------
	// To add a language: Add a field in the '$lang' array with appropriate text
	// note: some language definitions (international charset UTF-8 is used for all languages):
	//                                  =====================================================
	//       english: Lang = en
	//       russian: Lang = ru
	//       french: Lang = fr
	//       german: Lang = de
	//       greek: Lang = el
	//       hebrew: Lang = iw
	//       chinese: Lang = zh
	//       korean: Lang = ko
	//       japanese: Lang = ja
$lang = array (
	'Japanese' => array (
		// Language definition
		'Lang' => 'ja',
		'Display' => '日本語表示',
		// Title
		'Title' => 'パスワード変更',
		// Maintenance
		'Maintenance' => 'サーバーとの接続に失敗',
		// Form fields
		'text' => '全ての項目を埋めてください',
		'account' => 'アカウントID',
		'email' => 'メールアドレス',
		'old_pass' => '変更前のパスワード',
		'new_pass' => '新パスワード',
		'new_conf_pass' => '新パスワード(確認)',
		// Form buttons
		'Submit' => '変更',
		'Reset' => 'やり直し',
		// Errors
		'bad_account' => 'アカウントIDが無効',
		'bad_email' => 'メールアドレスが無効',
		'bad_email2' => 'メールアドレスが無効',
		'bad_email3' => 'メールアドレスが無効',
		'bad_email4' => 'メールアドレスが無効',
		'bad_email5' => 'メールアドレスが無効',
		'bad_email6' => 'メールアドレスが無効',
		'bad_email7' => 'メールアドレスが無効',
		'bad_email8' => 'メールアドレスが無効',
		'bad_old_pass' => '変更前のパスワードが無効',
		'bad_new_pass' => '新パスワードが無効',
		'bad_new_pass2' => '変更前後のパスワードが同じ',
		'bad_new_conf_pass' => '新パスワードが無効',
		'bad_new_conf_pass2' => '新パスワードと確認パスワードが違う',
		'bad_values' => 'IDまたはパスワードが違います',
		'bad_values_email' => 'IDまたはパスワード・メールアドレスが違います',
		// Success
		'Success' => 'パスワード変更に成功',
		// Copyright
		'Copyright' => 'Powered by Yor for Athena Project and Modified for Auriga.',
	),
	'English' => array (
		// Language definition
		'Lang' => 'en',
		'Display' => 'To display in English, click here.',
		// Title
		'Title' => 'PASSWORD CHANGE',
		// Maintenance
		'Maintenance' => 'Impossible to communicate with server. Sorry, you can not change your password now.',
		// Form fields
		'text' => 'Please, enter all values to change password:',
		'account' => 'Account name',
		'email' => 'Email of the account',
		'old_pass' => 'Old Password',
		'new_pass' => 'New Password',
		'new_conf_pass' => 'Confirm New Password',
		// Form buttons
		'Submit' => 'Submit',
		'Reset' => 'Reset',
		// Errors
		'bad_account' => 'Invalid account name (It must have between 4 to 23 characters).',
		'bad_email' => 'Invalid email (It must have between 3 to 39 characters).',
		'bad_email2' => 'Invalid email (It must have a @).',
		'bad_email3' => 'Invalid email (\'@\' can not be latest character).',
		'bad_email4' => 'Invalid email (\'.\' can not be latest character).',
		'bad_email5' => 'Invalid email (The last \'@\' can not be followed by a \'.\').',
		'bad_email6' => 'Invalid email (After the last \'@\' you can not have \'..\').',
		'bad_email7' => 'Invalid email (After the last \'@\' you can not have a \' (space)\').',
		'bad_email8' => 'Invalid email (After the last \'@\' you can not have a \';\').',
		'bad_old_pass' => 'Invalid old password (It must have between 4 to 23 characters).',
		'bad_new_pass' => 'Invalid new password (It must have between 4 to 23 characters).',
		'bad_new_pass2' => 'Invalid new password (new password must be different of old password).',
		'bad_new_conf_pass' => 'Invalid confirmed new password (It must have between 4 to 23 characters).',
		'bad_new_conf_pass2' => 'Invalid confirmed new password (new password and confirmed new password must be same).',
		'bad_values' => 'Server can not recognize you. Check your account name and old password please.',
		'bad_values_email' => 'Server can not recognize you. Check your account name, email and old password please.',
		// Success
		'Success' => 'Your password have been changed.',
		// Copyright
		'Copyright' => 'Powered by Yor for Athena Project and Modified for Auriga.',
	),
	'French' => array (
		// Language definition
		'Lang' => 'fr',
		'Display' => 'Pour afficher en Français, cliquez ici.',
		// Title
		'Title' => 'MODIFICATION DU MOT DE PASSE',
		// Maintenance
		'Maintenance' => 'Impossible de communiquer avec le serveur. Désolé, vous ne pouvez pas changer votre mot de passe maintenant.',
		// Form fields
		'text' => 'Merci d\'entrer les différentes valeurs pour modifier votre mot de passe:',
		'account' => 'Nom du compte',
		'email' => 'Email du compte',
		'old_pass' => 'Ancien mot de passe',
		'new_pass' => 'Nouveau mot de passe',
		'new_conf_pass' => 'Confirmation du nouveau mot de passe',
		// Form buttons
		'Submit' => 'Envoyer',
		'Reset' => 'Réinitialiser',
		// Errors
		'bad_account' => 'Nom de compte incorrect (Il doit avoir entre 4 et 23 caractères).',
		'bad_email' => 'Email incorrect (Il doit avoir entre 3 et 39 caractères).',
		'bad_email2' => 'Email incorrect (Il doit avoir un @).',
		'bad_email3' => 'Email incorrect (Le \'@\' ne peut pas être le dernier caractère).',
		'bad_email4' => 'Email incorrect (L\'email ne peut pas se terminer par un \'.\').',
		'bad_email5' => 'Email incorrect (Le dernier \'@\' ne peut pas être suivi par un \'.\').',
		'bad_email6' => 'Email incorrect (Après le dernier \'@\' vous ne pouvez pas avoir \'..\').',
		'bad_email7' => 'Email incorrect (Après le dernier \'@\' vous ne pouvez pas avoir un \' (espace)\').',
		'bad_email8' => 'Email incorrect (Après le dernier \'@\' vous ne pouvez pas avoir un \';\').',
		'bad_old_pass' => 'Ancien mot de passe incorrect (Il doit avoir entre 4 et 23 caractères).',
		'bad_new_pass' => 'Nouveau mot de passe incorrect (Il doit avoir entre 4 et 23 caractères).',
		'bad_new_pass2' => 'Nouveau mot de passe incorrect (Le nouveau mot de passe doit être différent de l\'ancien mot de passe).',
		'bad_new_conf_pass' => 'Confirmation du nouveau mot de passe incorrect (Il doit avoir entre 4 et 23 caractères).',
		'bad_new_conf_pass2' => 'Confirmation du nouveau mot de passe incorrect (Il doit identique au nouveau mot de passe).',
		'bad_values' => 'Le serveur ne vous reconnait pas. Vérifiez votre nom de compte et votre ancien mot de passe SVP.',
		'bad_values_email' => 'Le serveur ne vous reconnait pas. Vérifiez votre nom de compte, votre email et votre ancien mot de passe SVP.',
		// Success
		'Success' => 'Votre mot de passe a été modifié.',
		// Copyright
		'Copyright' => 'Créé par Yor pour le Projet Athéna et a Modifié pour Auriga.',
	),
	'Russian' => array (
		// Language definition
		'Lang' => 'ru',
		'Display' => 'Для выбора русского языка нажмите здесь.',
		// Title
		'Title' => 'Изменение пароля',
		// Maintenance
		'Maintenance' => 'Невозможно подключиться к серверу, вы не можете изменить пароль сейчас.',
		// Form fields
		'text' => 'Пожалуйста, укажите все значения полей:',
		'account' => 'Имя учетной записи',
		'email' => 'Адрес электронной почты',
		'old_pass' => 'Старый пароль',
		'new_pass' => 'Новый пароль',
		'new_conf_pass' => 'Подтверждение',
		// Form buttons
		'Submit' => 'Отправить',
		'Reset' => 'Сброс',
		// Errors
		'bad_account' => 'Неправильное имя учетной записи (должно быть не менее 4 и не более 23 символов).',
		'bad_email' => 'Неправильный адрес электронной почты (должно быть не менее 3 и не более 39 символов).',
		'bad_email2' => 'Неправильный адрес электронной почты (должно содержать символ @).',
		'bad_email3' => 'Неправильный адрес электронной почты (\'@\' не может быть последним символом).',
		'bad_email4' => 'Неправильный адрес электронной почты (\'.\' не может быть последним символом).',
		'bad_email5' => 'Неправильный адрес электронной почты (символ \'@\' не может продолжаться символом \'.\').',
		'bad_email6' => 'Неправильный адрес электронной почты (после символа \'@\' не может быть символа \'..\').',
		'bad_email7' => 'Неправильный адрес электронной почты (после символа \'@\' не может быть символа \'(пробел)\').',
		'bad_email8' => 'Неправильный адрес электронной почты (после символа \'@\' не может быть символа \';\').',
		'bad_old_pass' => 'Неправильный старый пароль (должен быть не менее 4 и не более 23 символов).',
		'bad_new_pass' => 'Неправильный новый пароль (должен быть не менее 4 и не более 23 символов).',
		'bad_new_pass2' => 'Неправильный новый пароль (новый пароль должен отличаться от старого).',
		'bad_new_conf_pass' => 'Неправильное подтверждение пароля (должен быть не менее 4 и не более 23 символов).',
		'bad_new_conf_pass2' => 'Неправильное подтверждение пароля (пароль и подтверждение должны быть одинаковыми).',
		'bad_values' => 'Сервер не распознает вашу учетную запись. Проверьте название учетной записи и старый пароль.',
		'bad_values_email' => 'Сервер не распознает вашу учетную запись. Проверьте название учетной записи, адрес электронной почты и старый пароль.',
		// Success
		'Success' => 'Ваш пароль изменен.',
		// Copyright
		'Copyright' => 'Автор: Yor для Athena Project и модифицированные для Auriga.',
	),
);
	
	// ---- End of languages texts
	// ---------------------------

// ------------ after this line, you change code, not only options.

	// check of http datas
	function NormalisationHHTP($tableau) {
		foreach($tableau as $cle=>$valeur) {
			if (!is_array($valeur)) { // It's a element, we act
				$tableau[$cle] = stripslashes($valeur);
			} else { // it's an array, we call recursivly
				$tableau[$cle] = NormalisationHHTP($valeur);
			}
		}
		return $tableau;
	}
	if (get_magic_quotes_gpc()) {
		$_POST = NormalisationHHTP($_POST);
		$_GET  = NormalisationHHTP($_GET);
	}

	// Get transmited language if it exists
	if (isset($_POST['language'])) {
		$Language = $_POST['language'];
	} else if (isset($_GET['language'])) {
		$Language = $_GET['language'];
	}
	// check value of the language
	if (!isset($lang[$Language])) {
		$Language = 'Japanese'; // Default value
	}

	// Get sended values
	if (isset($_POST['account'])) {
		$account = $_POST['account'];
	} else {
		$account = "";
	}
	if (isset($_POST['email'])) {
		$email = $_POST['email'];
	} else {
		$email = "";
	}
	if (isset($_POST['old_pass'])) {
		$old_pass = $_POST['old_pass'];
	} else {
		$old_pass = "";
	}
	if (isset($_POST['new_pass'])) {
		$new_pass = $_POST['new_pass'];
	} else {
		$new_pass = "";
	}
	if (isset($_POST['new_conf_pass'])) {
		$new_conf_pass = $_POST['new_conf_pass'];
	} else {
		$new_conf_pass = "";
	}

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">

<html>

<head>

	<meta http-equiv="content-type" content="text/html; charset=UTF-8">
	<?php
		if (isset($lang[$Language]['Lang'])) {
			echo '<meta http-equiv="Content-language" content="'.$lang[$Language]['Lang'].'">'."\n";
		} else {
			echo '<meta http-equiv="Content-language" content="en">'."\n";
		}
	?>
	<meta http-equiv="Content-Style-Type" content="text/css">
	<meta http-equiv="imagetoolbar" content="no">
	<meta content="Yor" name="author">

	<?php
		if (isset($css_style)) {
			echo '<link rel="stylesheet" href="'.$css_style.'" type="text/css">'."\n";
		}
	?>

	<title>Auriga - <?php echo htmlspecialchars($lang[$Language]['Title'], ENT_QUOTES) ?></title>

</head>

<SCRIPT type="text/javascript">
<!--
	function SubmitValues() {
		var last_arobas = document.passwd.email.value.indexOf("@");
		while (document.passwd.email.value.indexOf("@", last_arobas + 1) != -1) {
			last_arobas = document.passwd.email.value.indexOf("@", last_arobas + 1);
		}
		if (document.passwd.account.value.length < 4 || document.passwd.account.value.length > 23) {
			document.getElementById('Error').innerHTML = <?php echo "\"".htmlspecialchars($lang[$Language]['bad_account'], ENT_QUOTES)."\""; ?>;
			return false;
<?php if ($CheckEmail) { ?>
		} else if (document.passwd.email.value.length < 3 || document.passwd.email.value.length > 39) {
			document.getElementById('Error').innerHTML = <?php echo "\"".htmlspecialchars($lang[$Language]['bad_email'], ENT_QUOTES)."\""; ?>;
			return false;
		} else if (last_arobas == -1) {
			document.getElementById('Error').innerHTML = <?php echo "\"".htmlspecialchars($lang[$Language]['bad_email2'], ENT_QUOTES)."\""; ?>;
				return false;
		} else if ((last_arobas + 1) == document.passwd.email.value.length) {
				document.getElementById('Error').innerHTML = <?php echo "\"".htmlspecialchars($lang[$Language]['bad_email3'], ENT_QUOTES)."\""; ?>;
				return false;
		} else if (document.passwd.email.value.charAt(document.passwd.email.value.length - 1) == '.') {
				document.getElementById('Error').innerHTML = <?php echo "\"".htmlspecialchars($lang[$Language]['bad_email4'], ENT_QUOTES)."\""; ?>;
				return false;
		} else if (document.passwd.email.value.charAt(last_arobas + 1) == '.') {
				document.getElementById('Error').innerHTML = <?php echo "\"".htmlspecialchars($lang[$Language]['bad_email5'], ENT_QUOTES)."\""; ?>;
				return false;
		} else if (document.passwd.email.value.indexOf("..", last_arobas + 1) != -1) {
				document.getElementById('Error').innerHTML = <?php echo "\"".htmlspecialchars($lang[$Language]['bad_email6'], ENT_QUOTES)."\""; ?>;
				return false;
		} else if (document.passwd.email.value.indexOf(" ", last_arobas + 1) != -1) {
				document.getElementById('Error').innerHTML = <?php echo "\"".htmlspecialchars($lang[$Language]['bad_email7'], ENT_QUOTES)."\""; ?>;
				return false;
		} else if (document.passwd.email.value.indexOf(";", last_arobas + 1) != -1) {
				document.getElementById('Error').innerHTML = <?php echo "\"".htmlspecialchars($lang[$Language]['bad_email8'], ENT_QUOTES)."\""; ?>;
				return false;
<?php } ?>
		} else if (document.passwd.old_pass.value.length < 4 || document.passwd.old_pass.value.length > 23) {
			document.getElementById('Error').innerHTML = <?php echo "\"".htmlspecialchars($lang[$Language]['bad_old_pass'], ENT_QUOTES)."\""; ?>;
			return false;
		} else if (document.passwd.new_pass.value.length < 4 || document.passwd.new_pass.value.length > 23) {
			document.getElementById('Error').innerHTML = <?php echo "\"".htmlspecialchars($lang[$Language]['bad_new_pass'], ENT_QUOTES)."\""; ?>;
			return false;
		} else if (document.passwd.new_conf_pass.value.length < 4 || document.passwd.new_conf_pass.value.length > 23) {
			document.getElementById('Error').innerHTML = <?php echo "\"".htmlspecialchars($lang[$Language]['bad_new_conf_pass'], ENT_QUOTES)."\""; ?>;
			return false;
		} else if (document.passwd.new_pass.value != document.passwd.new_conf_pass.value) {
			document.getElementById('Error').innerHTML = <?php echo "\"".htmlspecialchars($lang[$Language]['bad_new_conf_pass2'], ENT_QUOTES)."\""; ?>;
			return false;
		} else if (document.passwd.new_pass.value == document.passwd.old_pass.value) {
			document.getElementById('Error').innerHTML = <?php echo "\"".htmlspecialchars($lang[$Language]['bad_new_pass2'], ENT_QUOTES)."\""; ?>;
			return false;
		} else {
			return true;
		}
	}

	function ResetValues() {
		document.passwd.account.value = "";
<?php if ($CheckEmail) { ?>
		document.passwd.email.value = "";
<?php } ?>
		document.passwd.old_pass.value = "";
		document.passwd.new_pass.value = "";
		document.passwd.new_conf_pass.value = "";
		return true;
	}
// -->
</SCRIPT>

<body>

	<table align="center" border="0" cellpadding="0" cellspacing="0">
	<tr>
		<td align="center" valign="top" width="100%%">

<?php
	// If include doesn't exist!
	if (!file_exists('auriga.php')) {
		// display simple page for maintenance
printf('
			<h3>'.htmlspecialchars($lang[$Language]['Maintenance'], ENT_QUOTES).'</h3>
');

	} else {
		include('auriga.php');
?>

<?php
	// don't display an error by default
	$error_message = "";
	// by default, password is not changed
	$result = false;
	// if player send form, check values
	if ($account != "" || ($CheckEmail && $email != "") || $old_pass != "" || $new_pass != "" || $new_conf_pass != "") {
		if ($CheckEmail) {
			$email_len = strlen($email);
			$last_arobas = strrchr($email, '@');
		}
		if (strlen($account) < 4 || strlen($account) > 23) {
			$error_message = $lang[$Language]['bad_account'];
		} else if ($CheckEmail && ($email_len < 3 || $email_len > 39)) {
			$error_message = $lang[$Language]['bad_email'];
		} else if ($CheckEmail && $last_arobas == false) {
			$error_message = $lang[$Language]['bad_email2'];
		} else if ($CheckEmail && $email[$email_len - 1] == '@') {
			$error_message = $lang[$Language]['bad_email3'];
		} else if ($CheckEmail && $email[$email_len - 1] == '.') {
			$error_message = $lang[$Language]['bad_email4'];
		} else if ($CheckEmail && $last_arobas[1] == '.') {
			$error_message = $lang[$Language]['bad_email5'];
		} else if ($CheckEmail && strstr($last_arobas, "..") != false) {
			$error_message = $lang[$Language]['bad_email6'];
		} else if ($CheckEmail && strchr($last_arobas, " ") != false) {
			$error_message = $lang[$Language]['bad_email7'];
		} else if ($CheckEmail && strchr($last_arobas, ";") != false) {
			$error_message = $lang[$Language]['bad_email8'];
		} else if (strlen($old_pass) < 4 || strlen($old_pass) > 23) {
			$error_message = $lang[$Language]['bad_old_pass'];
		} else if (strlen($new_pass) < 4 || strlen($new_pass) > 23) {
			$error_message = $lang[$Language]['bad_new_pass'];
		} else if (strlen($new_conf_pass) < 4 || strlen($new_conf_pass) > 23) {
			$error_message = $lang[$Language]['bad_new_conf_pass'];
		} else if (strcmp($new_pass, $new_conf_pass) != 0) {
			$error_message = $lang[$Language]['bad_new_conf_pass2'];
		} else if (strcmp($new_pass, $old_pass) == 0) {
			$error_message = $lang[$Language]['bad_new_pass2'];
		}
	}

	// if no error (datas seems valid)
	if ($error_message == "" &&
	    ($account != "" || ($CheckEmail && $email != "") || $old_pass != "" || $new_pass != "" || $new_conf_pass != "")) {
		// connect to server
		$ladmin_conect = new ladmin;
		if (!$ladmin_conect->connect($serverip, $adminpasswd, $serverport)) {
			$error_message = $lang[$Language]['Maintenance'];
		} else {
			// check old password and get id of the account
			$checkdata = $ladmin_conect->checkaccount($account, $old_pass);
			if ($checkdata == false) {
				if ($CheckEmail) {
					$error_message = $lang[$Language]['bad_values_email'];
				} else {
					$error_message = $lang[$Language]['bad_values'];
				}
			} else {
				if ($CheckEmail) {
					// Get account info and check email
					$accountdata = $ladmin_conect->accountinfo3($account);
					$accountdata['email'] = rtrim($accountdata['email']);
					if ($accountdata == false ||
					    (strcasecmp($accountdata['email'], "@") != 0 && strlen($accountdata['email']) > 0 && strcasecmp($accountdata['email'], $email) != 0)) {
						if ($CheckEmail) {
							$error_message = $lang[$Language]['bad_values_email'];
						} else {
							$error_message = $lang[$Language]['bad_values'];
						}
					}
				}
				// if no error, continue...
				if ($error_message == "") {
					// change password
					$result = $ladmin_conect->changepass($account, $new_pass);
					if ($result == false) {
						$error_message = $lang[$Language]['Maintenance'];
					} // else change is ok.
				}
			}
		}
		$ladmin_conect->close(); // close in all case (password can be incorrect and connection opened)
	}

	if ($result == true) {
printf('
			<h3>'.htmlspecialchars($lang[$Language]['Success'], ENT_QUOTES).'</h3>
');

	} else {
?>

			<table border="0" cellpadding="0" cellspacing="0" width="100%">
			<tr>
				<td align="center" valign="top">
					<?php
					// Display title
					print('<h2>'.htmlspecialchars($lang[$Language]['Title'], ENT_QUOTES).'</h2>'."\n");

					// display link to change language
					foreach($lang as $i => $j) {
						if ($i != $Language && isset($j['Display'])) {
							if (isset($j['Lang'])) {
								printf("\t\t\t\t\t".'<a href="'.$_SERVER['PHP_SELF'].'?language='.$i.'" lang="'.$j['Lang'].'">'.htmlspecialchars($j['Display'], ENT_QUOTES).'</a><br />'."\n");
							} else {
								printf("\t\t\t\t\t".'<a href="'.$_SERVER['PHP_SELF'].'?language='.$i.'">'.htmlspecialchars($j['Display'], ENT_QUOTES).'</a><br />'."\n");
							}
						}
					}
					printf("\t\t\t\t\t".'<br />'."\n");

					// here begin de form
					print("\t\t\t\t\t".'<form name="passwd" method="post" action="'.$_SERVER['PHP_SELF'].'?language='.$Language.'" onSubmit="return SubmitValues();">
						<table align="center" border="0" cellpadding="3" cellspacing="0">
						<tr align="center" >
							<td colspan="2" align="center">
								<br />
								'.htmlspecialchars($lang[$Language]['text'], ENT_QUOTES).'
							</td>
						</tr>

						<tr align="center">
							<td align="right">'.htmlspecialchars($lang[$Language]['account'], ENT_QUOTES).' :</td>
							<td align="left"><input type="text" name="account" value="'.htmlspecialchars($account, ENT_QUOTES).'" size="24" maxlength="24"></td>
						</tr>'."\n");
if ($CheckEmail) {
						print("\t\t\t\t\t".'<tr align="center">
							<td align="right">'.htmlspecialchars($lang[$Language]['email'], ENT_QUOTES).' :</td>
							<td align="left"><input type="text" name="email" value="'.htmlspecialchars($email, ENT_QUOTES).'" size="40" maxlength="40"></td>
						</tr>'."\n");
}
						print("\t\t\t\t\t".'<tr align="center">
							<td align="right">'.htmlspecialchars($lang[$Language]['old_pass'], ENT_QUOTES).' :</td>
							<td align="left"><input type="password" name="old_pass" value="" size="24" maxlength="24"></td>
						</tr>
						<tr align="center">
							<td align="right">'.htmlspecialchars($lang[$Language]['new_pass'], ENT_QUOTES).' :</td>
							<td align="left"><input type="password" name="new_pass" value="" size="24" maxlength="24"></td>
						</tr>
						<tr align="center">
							<td align="right">'.htmlspecialchars($lang[$Language]['new_conf_pass'], ENT_QUOTES).' :</td>
							<td align="left"><input type="password" name="new_conf_pass" value="" size="24" maxlength="24"></td>
						</tr>
						<tr align="center">
							<td colspan="2" align="center">
								<i><span id="Error" style="display:inline; color:red">'.htmlspecialchars($error_message, ENT_QUOTES).'</span></i>
							</td>
						</tr>
						</table>

						<br />
						<input type="submit" name="submit" value="'.htmlspecialchars($lang[$Language]['Submit'], ENT_QUOTES).'" />&nbsp;&nbsp;<input type="button" value="'.htmlspecialchars($lang[$Language]['Reset'], ENT_QUOTES).'" name="reset" onClick="ResetValues();" />
					</form>'."\n");
					?>
				</td>
			</tr>
			</table>
<?php
	} // if ($result == true) {
} // if (!file_exists('auriga.php')) {
?>
		</td>
	</tr>
	</table>

	<table align="center" border="0" cellpadding="0" cellspacing="0">
	<tr>
		<td align="center">
			<br />
			<?php
			// display copyright here
			echo '<i>'.htmlspecialchars($lang[$Language]['Copyright'], ENT_QUOTES).'</i><br />'."\n";
			?>
		</td>
	</tr>
	</table>

</body>

</html>
