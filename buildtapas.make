api = 2
core = 7.38

; Added for theme
projects[jquery_update][subdir] = contrib
projects[block_class][subdir] = contrib
projects[features_extra][subdir] = contrib
projects[views_bootstrap][subdir] = contrib
projects[ds][subdir] = contrib

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
projects[multiselect][subdir] = contrib

; Administrative
projects[admin_menu][subdir] = contrib
projects[node_export][subdir]  = migration
projects[uuid][subdir] = migration
projects[user_import][subdir] = migration
projects[backup_migrate][subdir] = migration

; Community
projects[sharethis][subdir] = contrib
projects[follow][subdir] = contrib
projects[profile2][subdir] = contrib

; Additional modules
projects[homebox][subdir] = contrib
projects[token][subdir] = contrib
projects[hierarchical_select][subdir] = contrib
projects[context][subdir] = contrib
projects[hook_post_action][subdir] = contrib
projects[prepopulate][subdir] = contrib
projects[crumbs][subdir] = contrib

; Search
projects[apachesolr][subdir] = contrib
projects[apachesolr_og][subdir] = contrib

; Dev modules
projects[devel][subdir] = develop
;projects[checklistapi][subdir] = develop
;projects[qa_checklist][subdir] = develop
projects[advanced_help][subdir] = develop
projects[site_install_hooks][subdir] = develop
projects[diff][subdir] = develop

; custom
projects[tapas-modules][type] = module
projects[tapas-modules][download][type] = git
projects[tapas-modules][download][url] = git://github.com/NEU-DSG/tapas-modules
projects[tapas-modules][download][branch] = feature/solr_indexing
projects[tapas-modules][download[branch][working-copy] = TRUE

projects[tapas-themes][type] = theme
projects[tapas-themes][download][type] = git
projects[tapas-themes][download][url] = git://github.com/NEU-DSG/tapas-themes
projects[tapas-themes][download][branch] = develop
projects[tapas-themes][download][working-copy] = TRUE
