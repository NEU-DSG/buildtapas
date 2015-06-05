api = 2
core = 7.37

; Contributed modules key dependencies
projects[ctools][subdir] = contrib
projects[views][subdir] = contrib
projects[views_bulk_operations][subdir] = contrib
projects[og][subdir] = contrib
projects[features][subdir] = contrib
projects[rules][subdir] = contrib
projects[entity][subdir] = contrib
projects[entityreference][subdir] = contrib

; Field types
projects[date][subdir] = contrib
projects[link][subdir] = contrib
projects[addressfield][subdir] = contrib
projects[name][subdir] = contrib

; Administrative
projects[admin_menu][subdir] = contrib
;projects[backup_migrate][subdir] = contrib
projects[node_export][subdir]  = migration
projects[uuid][subdir] = migration
projects[user_import][subdir] = migration

# taxonomy_csv's attempt maintain drush backwards compatibility breaks
# the drush commands in version seven. This patch fixes the issue by
# commenting out the v6 compatibility code.
projects[taxonomy_csv][subdir] = migration
projects[taxonomy_csv][patch] = https://www.drupal.org/files/issues/taxonomy_csv-drush_v6_taxocsv_import_compatibility-2310025-2.patch

; Community
projects[sharethis][subdir] = contrib
projects[follow][subdir] = contrib
projects[profile2][subdir] = contrib

; Additional modules
projects[homebox][subdir] = contrib
projects[token][subdir] = contrib
projects[jquery_update][subdir] = contrib
projects[hierarchical_select][subdir] = contrib

; Dev modules
projects[devel][subdir] = develop
;projects[checklistapi][subdir] = develop
;projects[qa_checklist][subdir] = develop
projects[advanced_help][subdir] = develop
projects[coder][subdir] = develop

; custom 
projects[tapas-modules][type] = module
projects[tapas-modules][download][type] = git
projects[tapas-modules][download][url] = git://github.com/NEU-DSG/tapas-modules
projects[tapas-modules][download][branch] = development
projects[tapas-modules][download[branch][working-copy] = TRUE

projects[tapas-themes][type] = theme
projects[tapas-themes][download][type] = git
projects[tapas-themes][download][url] = git://github.com/NEU-DSG/tapas-themes
projects[tapas-themes][download][branch] = redesign
projects[tapas-themes][download][working-copy] = TRUE

