# buildtapas
The Drupal build profile and drush makefile for installing the tapas project.

## First, Get your environment.
This might be your production server, the http://www.drupal.org/project/vdd vagrant box, or the the https://github.com/NEU-DSG/tapas-platter box.
If you are using Drupal's VDD box, you will also need to install the XML parsing PHP library by typing typing `sudo apt-get install php5-xsl`
If you use tapas-platter, this script will be called automagically -- skip to the 'After running the buildtapas.sh script' section.

## instructions for using buildtapas

  1. Download the buildtapas.sh file (yes, ONLY this file. It will clone/download/create everything else that it needs).
  2. Place it in the location where you want to install Drupal
  3. The five parameters are:
     * Username for exisiting MySQL account with sufficient permissions to create a new database
	  * The password for above MySQL account
	  * The name of the new drupal database to create
	  * the name of the new user to create for drupal to use to access this new database
	  * The new password that drupal should use to log in as the above-mentioned new user.

The website login will be username `admin` with a randomly generated password which will be shown at the end of the install process.

## After running the buildtapas.sh script

  1. Log in and change the 'admin' password.
	2. Under the 'TAPAS' section of the Modules page, enable the 'importtaxonomies' modules to populate the taxonomy values.
	3. Use Node Export's import feature to upload the basic page exports stored in the buildtapas subfolder.
	4. Use Node Export's import feature to upload the content (not stored in Github, because not all of it is public).
