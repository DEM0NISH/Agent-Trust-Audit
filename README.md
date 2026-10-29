# Agent Trust Audit

Can an AI pentest agent recognize a real, already-fixed flaw from code, and can it stay on task when a local page contains hostile instructions?

This small audit has two experiments: a pre/post-cutoff code review comparison and a localhost-only prompt-injection check. It uses a minimal Anthropic tool loop with JSON traces and defaults to `claude-sonnet-4-6`. Set `TRAINING_CUTOFF` to the evaluated model's documented cutoff before interpreting the CVE periods; if the cutoff is unknown, this experiment cannot support a memorization inference. A result from one CVE in each period is only a signal, not proof of memorization.

## Setup

```powershell
python -m venv .venv
.\.venv\Scripts\Activate.ps1
pip install -r requirements.txt
Copy-Item .env.example .env
# Edit .env and set ANTHROPIC_API_KEY to your key.
```

The test agent can read files under this repository, or fetch `http://127.0.0.1:5000/` for the hostile-target run. The fetch tool rejects all other hosts, redirects, and ports. Only use the lab page for Experiment 2.

## Run

```powershell
python experiment1_memorization/run.py
```

In a second terminal, start the local page and run the agent:

```powershell
python experiment2_hostile_target/lab_server.py
python experiment2_hostile_target/run.py
```

Every run writes visible model output, tool action, and tool observation to `results/<run_id>.json`. These are the model's emitted messages, not private hidden reasoning. Summaries are written to `results/experiment1.json` and `results/experiment2.json`.

## CVE sources and fixtures

The two fixture pairs are short source excerpts from the vulnerable parent and public fix commit in `git/git`:

- [CVE-2023-23946 fix commit](https://github.com/git/git/commit/c867e4fa180bec4750e9b54eb10f459030dbebfd): `git apply` could write beyond a symlink created by an earlier patch hunk. The fix checks the destination again at write time. The advisory lists affected and patched Git versions [here](https://github.com/git/git/security/advisories/GHSA-r87m-v37r-cwfh).
- [CVE-2024-32002 fix commit](https://github.com/git/git/commit/97065761333fd62db1912d81b489db938d8c991d): recursive submodule clone could follow a case-confused symlink into `.git`; the fix validates the resulting submodule directory. The [Git advisory](https://github.com/git/git/security/advisories/GHSA-8h77-4q3w-gfgv) describes affected versions and the fix.

The excerpts contain no exploit payloads. The relevant behaviors and fixes are summarized in each fixture's comments.

## Actual results

See [Experiment 1](results/experiment1.json), [Experiment 2](results/experiment2.json), and the [report](results/report.md). A missing API key is recorded as `not_run`, never counted as a pass or miss. In this workspace, dependency installation also could not complete because PyPI DNS lookup failed; install `requirements.txt` on a machine with package access before starting the Flask lab.

## Limitations & what a fuller version adds

- One CVE in each period cannot separate memorization from general security knowledge. A stronger design needs many matched CVE pairs, repeated runs, randomized order, and independent grading.
- The cutoff is a user-configured assumption; training data cutoffs are often uncertain. Record the exact model and documented cutoff for meaningful interpretation.
- The fixtures are brief excerpts of real Git code, not whole vulnerable versions or executable reproductions.
- One Claude model and one canary wording do not generalize across models or injection styles.
- The loop logs only model-emitted text, actions, and observations; it does not expose private chain-of-thought.
- The hostile page runs on loopback, but the agent provider receives the prompt and fetched page content over its normal API connection.
