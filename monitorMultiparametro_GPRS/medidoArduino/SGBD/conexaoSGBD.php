<?php
    /**
 * Classe de conexão ao banco de dados usando PDO no padrão Singleton.
 * Modo de Usar:
 * require_once './Database.class.php';
 * $db = Database::conexao();
 * E agora use as funções do PDO (prepare, query, exec) em cima da variável $db.
 */

class Database{
    #guara a conexão PDO.
    protected static $db;
    #Private construct - gatante que a classe so podera ser instanciada internamente
    private function __construct(){
        #SGBD utilizado
        $db_host    = "localhost";
        $db_name    = "monitor";
        $db_usuario = "postgres";
        $db_senha   = "190125";
        $db_driver  = "pgsql";
               
        try{
            #atribui objeto PDO à variável $db.
            self::$db = new PDO("$db_host:host=$db_host;
                                 dbname=$db_nam",$db_usuario,
                                 $db_senha);
            #garante que o PDO lance exceções.
            self::$db->setAttribute(PDO::ATTR_ERRMODE,
                        PDO::ERRMODE_EXCEPTION);

        }catch (PDOException $e){
            #grava um erro de conexao.
            $mensagemErro = "erro ao conectar...";
            echo $mensagemErro;
            die("Connection Error: " . $e->getMessage());                
            
        }
    }
    #Método estático - acessivel sem instanciação.
    public static function conexao(){
        #Garante uma única instância, se não tiver conexão cria uma nova
        if(!self::$db){
            new Database();
        }
        #Retorna a conexão.
        return self::$db;
    }
}
?>