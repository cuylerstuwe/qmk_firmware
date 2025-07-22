# Salembeats3 – Work-focused Layout for Preonic (Non-Encoder)

This layout ports the work-optimized *salembeats2encoder* keymap to Preonic revisions **without** the rotary encoder.

Highlights:

* All layers and key positions come from the encoder version, keeping muscle-memory intact.
* The encoder push-button (`ENCODER_PRESS`) has been replaced by `KC_F1` in the matrix.
* All encoder-related code and build flags have been removed so it compiles on classic Preonic PCBs.

Compile with:

```bash
qmk compile -kb preonic -km salembeats3
``` 