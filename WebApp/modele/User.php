<?php
include("Connexion.php");

class User extends Connexion
{



	//la fontion qui permet d'envoyer la requet SQL et retourn la reponse sous form table
	public function tableRequet($sql)
	{
		$table = array();

		$req = $this->getPDO()->query($sql);

		while ($data = $req->fetch()) {
			$table[] = $data;
		}
		return $table;
	}

	/************************************/
	/***** CONNEXION ET INSCRIPTION *****/
	/************************************/

	// la fonction de l'inscription //SYSDATE

	public function SendData($flameValue,$GazValue)
	{
		$sql = "INSERT INTO data (GazValue,FlameValue,Date) VALUES ($flameValue,$GazValue,NOW());";
		
		$req = $this->getPDO()->query($sql);
		return (!!$req);
	}


	//la fonction d'authentification

	public function valide($email, $mdp)
	{

		$user = array();
		$sql = "SELECT * FROM user WHERE Email='$email' AND MDP='$mdp'";
		$req = $this->getPDO()->query($sql);

		if ($data = $req->fetch()) {
			$user = $data;
			//Verifie si la sensibilité à case de mot de passe
			if (strcmp($user['MDP'], $mdp) != 0) {
				return false;
			}
			return $user;
		} else {

			return false;
		}
	}

	public function verifie_email($email)
	{
		$user = array();
		$sql = "SELECT email FROM user WHERE Email='$email'";
		$req = $this->getPDO()->query($sql);

		if ($data = $req->fetch()) {
			$user = $data;
			return false;
		} else {

			return true;
		}
	}

	
	public function dataDisply()
	{

		$sql = "SELECT * FROM data ORDER BY id DESC limit 0,30 ";

		return $this->tableRequet($sql);

		// $req = $this->getPDO()->query($sql);


		// 	return $req;

	}

}

?>