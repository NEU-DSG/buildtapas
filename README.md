# buildtapas
The Drupal build profile and drush makefile for installing the tapas project.

## First, Get your environment.
This might be your production server, the http://www.drupal.org/project/vdd vagrant box, or the the https://github.com/NEU-DSG/tapas-platter box.
If you are using Drupal's VDD box, you will also need to install the XML parsing PHP library by typing typing `sudo apt-get install php5-xsl`
If you use tapas-platter, this script will be called automagically -- skip to the 'After running the buildtapas.sh script' section.

## instructions for using buildtapas

	1. Download two just two files (yes, just these two. They will pull down the rest of what is needed.)
	  * buildtapas.sh
		* stub.make
  1. Place them in the location where you want to install Drupal
  1. The five parameters are:
    * Username for exisiting MySQL account with sufficient permissions to create a new database
	  * The password for above MySQL account
	  * The name of the new drupal database to create
	  * the name of the new user to create for drupal to use to access this new database
	  * The new password that drupal should use to log in as the above-mentioned new user.

The website login will be username `admin` with a randomly generated password which will be shown at the end of the install process.

## After running the buildtapas.sh script

  1. Log in and change the 'admin' password.
  1. Under the 'TAPAS' section of the Modules page, enable the 'importtaxonomies' modules to populate the taxonomy values.
	1. Go into the UUID module's settings and hit the "Create Missing UUID's" button
  1. Use Node Export's import feature to upload the basic page exports stored in the buildtapas subfolder.
  1. Use Node Export's import feature to upload the content (not stored in Github, because not all of it is public).
  1. Manually set 'sharethis' settings. Couldn't figure out a way to do it programatically.


## Files

<dl>
	<dt>README.me</dt>
	<dd> This instruction set. </dd>
 	<dt> buildtapas.info: </dt>
	<dd>Gives the version of Drupal to install and the list of modules to enable.</dd>
 	<dt> buildtapas.install: </dt>
	<dd>Enables the theme, creates filter formats, and adds RDF.</dd>
 	<dt> buildtapas.make: </dt>
	<dd>Tells <strong>drush make</strong> what version of Drupal to download and install, 
			and what modules & themes to download and install.</dd>
 	<dt> buildtapas.profile: </dt>
	<dd>Automatically selects this profile in Drupal's instalation GUI, so that the user doesn't need to intervene/use the gui.</dd>
 	<dt> buildtapas.sh:</dt>
	<dd><ol>
		<li>Calls <strong>drush make</strong> on the <strong>stub.make</strong> file. This will cause Drupal and all 
		   needed repositories and modules (including buildtapas) to be downloaded.</li>
		<li>Creates the MySQL database that Drupal will use</li>
		<li>Runs the Drupal installation script, telling it to use <strong>buildtapas</strong> as the 
		   installation profile.</li>
		<li>Calls a few additional cleanup Drush commands</li>
	</ol></dd>
 	<dt> buildtapas_database.sql </dt>
	<dd></dd>
 	<dt> buildtapas_usersettings.inc </dt>
	<dd></dd>
	<dt> stub.make</dt>
	<dd> Stub makefile tells <strong>drush make</strong> to pull down this full buildtapas directory, and to install Drupal.
	</dd>
</dl>
