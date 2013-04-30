<?php

require '/tmhOAuth/tmhOAuth.php';
require '/tmhOAuth/tmhUtilities.php';

class twitController {

    public $tmhOAuth;
    public $messages = array();

    public function __destruct() {
        unset($tmhOAuth);
    }

    public function __construct() {
        $this->_setCredentials();
    }

    public function _setCredentials() {
        $consumer_key = variable_get('twitter_consumer_key', '');
        $consumer_secret = variable_get('twitter_consumer_secret', '');
        $user_token = variable_get('twitter_user_token', '');
        $user_secret = variable_get('twitter_user_secret', '');

        if (empty($consumer_key) || empty($consumer_secret) || empty($user_token) || empty($user_secret)) {
            return FALSE;
        }

        $this->tmhOAuth = new tmhOAuth(array(
              'consumer_key' => $consumer_key,
              'consumer_secret' => $consumer_secret,
              'user_token' => $user_token,
              'user_secret' => $user_secret,
            ));
    }

    public function addMessages($str_message) {
        if (empty($str_message) || $str_message == "") {
            return FALSE;
        }
        if (strlen($str_message) < 139) {
            $this->messages[] = $str_message;
        }
        else {
            while (strlen($str_message) > 139) {
                $msg = substr($str_message, 0, 139);
                $str_message = substr($str_message, 140);
                $this->messages[] = $msg;
                unset($msg);
            }
        }
    }

    public function setStatus() {
        if (!is_array($this->messages) && count($this->messages) == 0) {
            return FALSE;
        }
        foreach ($this->messages as $twit) {

            $code = $this->tmhOAuth->request('POST', $this->tmhOAuth->url('1/statuses/update'), array(
              'status' => $twit
                ));

            if ($code != 200) {
                return FALSE;
            }
        }
        return TRUE;
    }

}

