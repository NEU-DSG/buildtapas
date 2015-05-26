# buildtapas
The Drupal build profile and drush makefile for installing the tapas project.

## instructions for setting up the virtual box
 1. Get Vagrant for Drupal development at https://www.drupal.org/project/vdd
 2. Follow the directions at the above link to install
 3. Install the XML parsing php library by typing `sudo apt-get install php5-xml`

## instructions for using buildtapas

  1. Download the buildtapas.sh file (yes, ONLY this file. It will clone/download/create everything else that it needs).
  2. Place it in the location where you want to install Drupal
  3. The five parameters are:
     * Username for exisiting MySQL account with sufficient permissions to create a new database
	  * The password for above MySQL account
	  * The name of the new drupal database to create
	  * the name of the new user to create for drupal to use to access this new database
	  * The new password that drupal should use to log in as the above-mentioned new user.

I apologize for the lengthy command line, but it should be obvious why none of these parameters can be stored in a publically accessible file.


The website login will be username `admin` with a randomly generated password which will be shown at the end of the install process.
