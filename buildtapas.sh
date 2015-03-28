#!/bin/bash

## I. Usage statement
if [ "$5" == "" ]
then
	echo "Usage:";
	echo "tapasbuild.sh has five arguments, all mandatory:";
	echo "   * Username of an existing MySQL account with";
	echo "     sufficient permissions to create a database";
	echo "   * Password to above MySQL account";
	echo "   * Name of the new drupal database to create";
	echo "   * Username that drupal should use to";
	echo "     manage this database";
	echo "   * Password that drupal should use to access";
	echo "     this database";
	echo "";
	echo "I apologize for the lengthy command line, but it";
	echo "should be clear why none of these parameters can";
	echo "be stored in a publically accessable file.";
	exit;
fi

## II. Create stub.make
echo "api: 2" > stub.make;
echo "core: 7.35" >> stub.make;
echo "" >> stub.make;
echo "projects[drupal][type] = core" >> stub.make;
echo "projects[drupal][version] = 7.35" >> stub.make;
echo "" >> stub.make;
echo "projects[buildtapas][type] = profile" >> stub.make;
echo "projects[buildtapas][download][type] = git" >> stub.make;
echo "projects[buildtapas][download][url] = git://github.com/NEU-DSG/buildtapas" >> stub.make;

## III. Run the stub.make
# This will:
#    * Download drupal
#    * clone the buildtapas installation profile
#    * run the buildtapas.make drush make file, which will
#      download the contributed and custom modules/features/
#      themes/etc as needed.

drush -y make stub.make;


## IV. Create the Drupal database

mysql -u $1 -p $2 -e"set @dbname='$3'; set @uname='$4'; set @pw='$5';  `cat profiles/buildtapas/buildtapas_database.sql`";


## V. Run the installation script.

# This will:
#    * Install drupal
#    * enable modules
#    * miscelaneous installation tasks

drush -y si buildtapas;

