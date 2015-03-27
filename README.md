# buildtapas
The Drupal build profile and drush makefile for installing the tapas project.

Copy and paste the following into a plaintext file named tapas.make:

```
core = 7.35
api = 2

projects[buildtapas][type] = profile
projects[buildtapas][download][type] = git
projects[buildtapas][download][url] = git://github.com/NEU-DSG/buildtapas

```

(Instructions coming for how to run the tapas make file to pull down Drupal, the modules, and this installation profile using drush)
