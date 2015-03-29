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
echo "=============================================="
echo "Creating stub.make file..."
echo "=============================================="
echo "api = 2" > stub.make;
echo "core = 7.35" >> stub.make;
echo "" >> stub.make;
echo "projects[drupal][type] = core" >> stub.make;
echo "projects[drupal][version] = 7.35" >> stub.make;
#echo "" >> stub.make;
#echo "; See https://www.drupal.org/node/1432374 for path info. legacy" >> stub.make;
#echo "; check causes problems with custom profiles." >> stub.make;
echo "projects[drupal][patch][] = https://www.drupal.org/files/1093420-22.patch" >> stub.make;
echo "" >> stub.make;
echo "projects[buildtapas][type] = profile" >> stub.make;
echo "projects[buildtapas][download][type] = git" >> stub.make;
echo "projects[buildtapas][download][url] = git://github.com/NEU-DSG/buildtapas" >> stub.make;

echo "Continue to drush make?"
select yn in "Yes" "No"; do
    case $yn in
        Yes ) break;;
        No ) exit;;
    esac
done

## III. Run the stub.make
echo "=============================================="
echo "Run drush make on the stub.make..."
echo "=============================================="
# This will:
#    * Download drupal
#    * clone the buildtapas installation profile
#    * run the buildtapas.make drush make file, which will
#      download the contributed and custom modules/features/
#      themes/etc as needed.

drush -y make stub.make;



echo "Continue to create database?"
select yn in "Yes" "No"; do
    case $yn in
        Yes ) break;;
        No ) exit;;
    esac
done

## IV. Create the Drupal database
echo "=============================================="
echo "Create the empty drupal database in mysql..."
echo "=============================================="
echo "command: mysql -u $1 -p$2 -e\"set @dbname='$3'; set @uname='$4'; set @pw='$5';  `cat profiles/buildtapas/buildtapas_database.sql`\"";

mysql -u $1 -p$2 -e"set @dbname='$3'; set @uname='$4'; set @pw='$5';  `cat profiles/buildtapas/buildtapas_database.sql`";


echo "Continue to run instalation script?"
select yn in "Yes" "No"; do
    case $yn in
        Yes ) break;;
        No ) exit;;
    esac
done
## V. Run the installation script.
echo "=============================================="
echo "Run drush site-install on the buildtapas profile...."
echo "=============================================="
# This will:
#    * Install drupal
#    * enable modules
#    * miscelaneous installation tasks
echo "Command: drush -y si buildtapas --db-url=mysql://$1:$2@localhost:8080/$3 username=$4 pass=$5 dbname=$3"
drush -y si buildtapas --db-url=mysql://$1:$2@localhost:8080/$3 username=$4 pass=$5 dbname=$3

echo "Continue to rebuild permissions?"
select yn in "Yes" "No"; do
    case $yn in
        Yes ) break;;
        No ) exit;;
    esac
done
## VI. Rebuild permissions
echo "=============================================="
echo "Rebuilding permissions...."
echo "=============================================="
drush php-eval 'node_access_rebuild();'
