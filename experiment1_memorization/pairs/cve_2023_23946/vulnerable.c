/* Excerpt from git/git apply.c at c867e4fa180bec4750e9b54eb10f459030dbebfd^.
 * The up-front path check can miss a symlink created by an earlier hunk.
 */
if (state->cached)
    return 0;

res = try_create_file(state, path, mode, buf, size);
if (res < 0)
    return -1;
