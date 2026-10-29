/* Excerpt from git/git commit 97065761333fd62db1912d81b489db938d8c991d.
 * Refuse a cloned path containing unexpected entries, including symlinks.
 */
if (run_command(&cp))
    die(_("clone of '%s' into submodule path '%s' failed"),
        clone_data->url, clone_data_path);

if (clone_data->require_init && !stat(clone_data_path, &st) &&
    !dir_contains_only_dotgit(clone_data_path)) {
    char *dot_git = xstrfmt("%s/.git", clone_data_path);
    unlink(dot_git);
    free(dot_git);
    die(_("directory not empty: '%s'"), clone_data_path);
}
} else {
