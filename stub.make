api = 2
core = 7.43

projects[drupal][type] = core
projects[drupal][version] = 7.43

# This patch is to prevent user_role_grant_permissions from crashing
projects[drupal][patch[] = https://www.drupal.org/files/user_role_grant_permission_fails_when_module_is_missing-1249952-2.patch

projects[buildtapas][type] = profile
projects[buildtapas][download][type] = git
projects[buildtapas][download][url] = git://github.com/NEU-DSG/buildtapas
projects[buildtapas][download][branch] = feature/shared_repos
