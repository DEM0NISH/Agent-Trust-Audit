/* Excerpt from git/git builtin/submodule--helper.c at
 * 97065761333fd62db1912d81b489db938d8c991d^.
 * A recursive clone is started at the selected submodule path; this version
 * does not validate the resulting directory contents after clone.
 */
if (run_command(&cp))
    die(_("clone of '%s' into submodule path '%s' failed"),
        clone_data->url, clone_data_path);
} else {
    char *path;
