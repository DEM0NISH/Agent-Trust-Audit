/* Excerpt from git/git commit c867e4fa180bec4750e9b54eb10f459030dbebfd.
 * The write-time check catches symlinks introduced by earlier patch hunks.
 */
if (state->cached)
    return 0;

if (path_is_beyond_symlink(state, path))
    return error(_("affected file '%s' is beyond a symbolic link"), path);

res = try_create_file(state, path, mode, buf, size);
if (res < 0)
    return -1;
