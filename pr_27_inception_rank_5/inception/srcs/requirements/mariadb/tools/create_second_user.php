<?php
// Load WordPress functions
require_once('/var/www/html/wp-load.php');

if (!username_exists('editor42')) {
    // Create user: username, password, email
    wp_create_user('editor42', 'editorpassword', 'editor42@example.com');
}
?>
