# Writing rules (ASD-STE style technical English)

All prose in this repo follows Simplified Technical English practice
(ASD-STE100 spirit). No AI filler. Write for a reader who disassembles.

## Sentence rules

- One topic per sentence. Maximum 25 words per sentence.
- Active voice. Present tense for facts, past tense for observations.
- No present participles as openers ("Using X...", "Having seen...").
- One instruction per sentence in procedures.

## Word rules

- One word, one meaning. "Image" is always a ROM dump. "Set" is always
  a block set. "Table" is always a descriptor table. Do not rotate
  synonyms.
- Verbs, not nominalizations: "uploads", not "performs an upload of".
- Approved vague words are banned: leverage, facilitate, delve,
  landscape, robust, seamless, utilize (use "use").
- No throat-clearing: "it is worth noting", "it turns out",
  "interesting", "surprisingly", "as an AI". State the fact.
- No hype adjectives on our own work: "clean", "elegant", "powerful".
  Let the bytes carry it.
- Hedge once or not at all. "Unconfirmed" beats
  "it is possible that this might potentially suggest".

## Evidence rules

- Every claim carries its address: file, hex offset, function, or
  register. `0x2CAD16`, not "the gate code".
- Observed before inferred. Mark the line: `observed:`, `inferred:`,
  `open:`. Never mix them in one sentence.
- Numbers exact: `19/24`, `miss 1/24`. Never "most", "many", "few".

## Structure rules

- Headings state content, not process: "HPI version poll", not
  "How we found the poll".
- Tables for mappings only (max 4 columns, short cells). Prose
  comparisons become lists.
- No summary paragraph that restates the section above it. If the
  section is correct, it needs no recap.

## Banned patterns

- "In conclusion / In summary / TL;DR" (delete the recap, keep the fact)
- "X is not just Y, it is Z" (write Z)
- "Whether A or B" openers (state which)
- Rhetorical questions (write the answer as a statement)
- Em dashes as argument glue (use a period; two sentences)
