
## I. Usage statement
if [ "$5" == "" ]
then
	echo "Usage:";
	echo "tapasbuild.sh has five arguments, all mandatory:";
	echo "   * Username of an existing MySQL account with";
	echo "     sufficient permissions to create a database";
	echo "   * Password for the above user";
	echo "   * Name of the new drupal database to create";
	echo "   * Username that drupal should use to";
	echo "     manage this database";
	echo "   * Password that drupal should use to access";
	echo "     this database";
	echo "";
	exit;
fi

## II. Verify presence of Stub.make

stubfile="./stub.make"

if [ -f "$stubfile"]
then
	echo "Stubfile found: $stubfile"
else
	echo "This script requires the stub.make from"
	echo "http://www.github.com/NEU-DSG/buildtapas/stub.make"
	echo "to be in the same directory. Please download this file."
	exit 1
fi

## III. Run the stub.make
echo "=============================================="
echo "Runing drush make on the stub.make..."
echo "=============================================="
# This will:
#    * Download drupal
#    * clone the buildtapas installation profile
#    * run the buildtapas.make drush make file, which will
#      download the contributed and custom modules/features/
#      themes/etc as needed.

drush -y make stub.make;

## IV. Create the Drupal database
echo "=============================================="
echo "Create the empty drupal database in mysql..."
echo "=============================================="
echo "command: mysql -u $1 -p$2 -e\"set @dbname='$3'; set @uname='$4'; set @pw='$5';  `cat profiles/buildtapas/buildtapas_database.sql`\"";

mysql -u $1 -p$2 -e"set @dbname='$3'; set @uname='$4'; set @pw='$5';  `cat profiles/buildtapas/buildtapas_database.sql`";

## V. Run the Drupal installation script.
echo "=============================================="
echo "Run drush site-install on the buildtapas profile...."
echo "=============================================="
# This will:
#    * Install drupal
#    * enable modules
#    * miscelaneous installation tasks
echo "Command: drush -y si buildtapas --db-url=mysql://$1:$2@localhost:8080/$3 username=$4 pass=$5 dbname=$3"
drush -y si buildtapas --db-url=mysql://$1:$2@localhost:8080/$3 username=$4 pass=$5 dbname=$3

## VI. Additional drush commands
echo "=============================================="
echo "Additional drush commands and other cleanup...."
echo "=============================================="

# http://drupal.stackexchange.com/questions/159023/set-variable-site-name-in-installation-profile
# Inelegant solution since it bypasses localization, but it does the job for now.
drush -y vset site_name "TAPAS Project"
drush -y vset theme_default "tapas_redesign"
drush -y vset admin_theme "tapas_redesign"
drush -y vset clean_url TRUE
drush -y vset user_pictures TRUE
drush -y vset user_picture_dimentions "200x200"

# Turning off some modules that the 'standard' profile turns on
drush -y dis dashboard overlay shortcut toolbar

# Removing two "sample" features that conflict with our custom features
rm -r profiles/buildtapas/modules/contrib/og/og_example
rm -r profiles/buildtapas/modules/contrib/date/date_migrate/date_migrate_example

## VII. Rebuild permissions
echo "=============================================="
echo "Rebuilding permissions and updating variables...."
echo "=============================================="
drush php-eval 'node_access_rebuild();'
