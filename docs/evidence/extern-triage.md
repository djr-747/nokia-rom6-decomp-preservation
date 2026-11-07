# Extern triage register

Generated 2026-11-07 from `build/recombine.json` span map + `program.be16` bytes.
Classes: OFF-IMAGE (target outside the 65536-word mask image: XPC page, MCU-uploaded);
ZERO-WORD (target reads 0x0000 in the mask dump: RAM-resident at runtime, not mask ROM);
HW (hardware/emulator-provided op, no ROM target); INTERIOR (join into owned span, no C entry);
ASM-ONLY (owner span has no C yet: forward placeholder); REBOUND (now calls the real C entry).

## OFF-IMAGE (uploaded page, permanently extern)
- `far_18060` -> 0x18060: outside 64K mask image (65,536 words measured); fcall/far target, XPC page.
  Refs: 2 sites (aff9,b062). Evidence: README paged-program blocks; 00-overview upload model.
- `far_180A7` -> 0x180A7: outside 64K mask image (65,536 words measured); fcall/far target, XPC page.
  Refs: 2 sites (b036,b0a1). Evidence: README paged-program blocks; 00-overview upload model.
- `far_1A260` -> 0x1A260: outside 64K mask image (65,536 words measured); fcall/far target, XPC page.
  Refs: 3 sites (b036,b0a1,b0e8). Evidence: README paged-program blocks; 00-overview upload model.
- `far_1A7F1` -> 0x1A7F1: outside 64K mask image (65,536 words measured); fcall/far target, XPC page.
  Refs: 2 sites (53ba,53d9). Evidence: README paged-program blocks; 00-overview upload model.
- `far_1A7F8` -> 0x1A7F8: outside 64K mask image (65,536 words measured); fcall/far target, XPC page.
  Refs: 2 sites (53ba,53d9). Evidence: README paged-program blocks; 00-overview upload model.
- `far_1A86A` -> 0x1A86A: outside 64K mask image (65,536 words measured); fcall/far target, XPC page.
  Refs: 1 sites (4c41). Evidence: README paged-program blocks; 00-overview upload model.
- `far_1A886` -> 0x1A886: outside 64K mask image (65,536 words measured); fcall/far target, XPC page.
  Refs: 1 sites (4c41). Evidence: README paged-program blocks; 00-overview upload model.
- `far_1A8FD` -> 0x1A8FD: outside 64K mask image (65,536 words measured); fcall/far target, XPC page.
  Refs: 3 sites (b036,b0a1,b0e8). Evidence: README paged-program blocks; 00-overview upload model.
- `far_1AA2C` -> 0x1AA2C: outside 64K mask image (65,536 words measured); fcall/far target, XPC page.
  Refs: 2 sites (36f0,3753). Evidence: README paged-program blocks; 00-overview upload model.
- `sub_1A425` -> 0x1A425: outside 64K mask image (65,536 words measured); fcall/far target, XPC page.
  Refs: 1 sites (b017). Evidence: README paged-program blocks; 00-overview upload model.
- `sub_1A839` -> 0x1A839: outside 64K mask image (65,536 words measured); fcall/far target, XPC page.
  Refs: 1 sites (b017). Evidence: README paged-program blocks; 00-overview upload model.

## ZERO-WORD (RAM-resident, permanently extern)
- `frag_0700` -> 0x0700: reads 0x0000 in program.be16; called from 1 sites (4c29).
- `frag_0702` -> 0x0702: reads 0x0000 in program.be16; called from 1 sites (4c2f).
- `frag_0704` -> 0x0704: reads 0x0000 in program.be16; called from 1 sites (4c35).
- `frag_0706` -> 0x0706: reads 0x0000 in program.be16; called from 1 sites (4c3b).
- `frag_1000` -> 0x1000: reads 0x0000 in program.be16; called from 1 sites (4ff6).
- `helper_0594` -> 0x0594: reads 0x0000 in program.be16; called from 10 sites (44b2,44bd,457f,4590,91bd,91f2,9217,924c).
- `helper_0598` -> 0x0598: reads 0x0000 in program.be16; called from 1 sites (698b).
- `helper_05A0` -> 0x05A0: reads 0x0000 in program.be16; called from 2 sites (2e2f,84af).
- `helper_05B4` -> 0x05B4: reads 0x0000 in program.be16; called from 2 sites (6f79,712d).
- `helper_05C6` -> 0x05C6: reads 0x0000 in program.be16; called from 1 sites (96bd).
- `helper_05CC` -> 0x05CC: reads 0x0000 in program.be16; called from 1 sites (99a4).
- `helper_0606` -> 0x0606: reads 0x0000 in program.be16; called from 1 sites (4348).
- `helper_061C` -> 0x061C: reads 0x0000 in program.be16; called from 1 sites (a109).
- `helper_0648` -> 0x0648: reads 0x0000 in program.be16; called from 1 sites (84cf).
- `helper_0654` -> 0x0654: reads 0x0000 in program.be16; called from 2 sites (a2c3,a3d5).
- `helper_0656` -> 0x0656: reads 0x0000 in program.be16; called from 2 sites (a3e1,a4ba).
- `helper_0658` -> 0x0658: reads 0x0000 in program.be16; called from 2 sites (a4d5,a4de).
- `helper_065A` -> 0x065A: reads 0x0000 in program.be16; called from 3 sites (a5c6,a5d2,a5e1).
- `helper_0660` -> 0x0660: reads 0x0000 in program.be16; called from 1 sites (a806).
- `helper_06C8` -> 0x06C8: reads 0x0000 in program.be16; called from 1 sites (9dd7).
- `helper_06DE` -> 0x06DE: reads 0x0000 in program.be16; called from 2 sites (bf8c,bfaa).
- `helper_06F4` -> 0x06F4: reads 0x0000 in program.be16; called from 1 sites (45fa).
- `sub_052A` -> 0x052A: reads 0x0000 in program.be16; called from 3 sites (4444,4453,4557).
- `sub_0590` -> 0x0590: reads 0x0000 in program.be16; called from 2 sites (8813,8a45).
- `sub_0592` -> 0x0592: reads 0x0000 in program.be16; called from 4 sites (8641,864e,8653,8675).
- `sub_0594` -> 0x0594: reads 0x0000 in program.be16; called from 2 sites (44fd,4533).
- `sub_0598` -> 0x0598: reads 0x0000 in program.be16; called from 5 sites (5d38,5e7d,69a9,71a3,71d8).
- `sub_059A` -> 0x059A: reads 0x0000 in program.be16; called from 2 sites (af14,af3e).
- `sub_059C` -> 0x059C: reads 0x0000 in program.be16; called from 21 sites (4ba8,4ee0,4f3a,4ff6,500b,50b2,516a,51d8).
- `sub_059E` -> 0x059E: reads 0x0000 in program.be16; called from 9 sites (4858,4944,4af3,4b2c,7c57,7ca5,7fc6,7ff4).
- `sub_05A0` -> 0x05A0: reads 0x0000 in program.be16; called from 4 sites (2e64,37d8,3938,8413).
- `sub_05A4` -> 0x05A4: reads 0x0000 in program.be16; called from 1 sites (5d38).
- `sub_05A8` -> 0x05A8: reads 0x0000 in program.be16; called from 1 sites (b358).
- `sub_05AA` -> 0x05AA: reads 0x0000 in program.be16; called from 1 sites (3d3d).
- `sub_05B0` -> 0x05B0: reads 0x0000 in program.be16; called from 1 sites (e7ef).
- `sub_05B2` -> 0x05B2: reads 0x0000 in program.be16; called from 2 sites (36fb,8bd3).
- `sub_05B6` -> 0x05B6: reads 0x0000 in program.be16; called from 1 sites (3199).
- `sub_05B8` -> 0x05B8: reads 0x0000 in program.be16; called from 2 sites (2983,2a8a).
- `sub_05BA` -> 0x05BA: reads 0x0000 in program.be16; called from 1 sites (938c).
- `sub_05BC` -> 0x05BC: reads 0x0000 in program.be16; called from 1 sites (93ce).
- `sub_05BE` -> 0x05BE: reads 0x0000 in program.be16; called from 1 sites (942e).
- `sub_05CE` -> 0x05CE: reads 0x0000 in program.be16; called from 1 sites (99e6).
- `sub_05D0` -> 0x05D0: reads 0x0000 in program.be16; called from 1 sites (9a11).
- `sub_05D2` -> 0x05D2: reads 0x0000 in program.be16; called from 1 sites (9a50).
- `sub_05D6` -> 0x05D6: reads 0x0000 in program.be16; called from 1 sites (952e).
- `sub_05EA` -> 0x05EA: reads 0x0000 in program.be16; called from 1 sites (c851).
- `sub_05EC` -> 0x05EC: reads 0x0000 in program.be16; called from 1 sites (c7b1).
- `sub_05F6` -> 0x05F6: reads 0x0000 in program.be16; called from 1 sites (2875).
- `sub_05F8` -> 0x05F8: reads 0x0000 in program.be16; called from 1 sites (296a).
- `sub_05FC` -> 0x05FC: reads 0x0000 in program.be16; called from 1 sites (5b18).
- `sub_0606` -> 0x0606: reads 0x0000 in program.be16; called from 2 sites (425f,4315).
- `sub_0608` -> 0x0608: reads 0x0000 in program.be16; called from 1 sites (434f).
- `sub_0610` -> 0x0610: reads 0x0000 in program.be16; called from 1 sites (918c).
- `sub_0620` -> 0x0620: reads 0x0000 in program.be16; called from 1 sites (2e84).
- `sub_0624` -> 0x0624: reads 0x0000 in program.be16; called from 1 sites (2d8f).
- `sub_0626` -> 0x0626: reads 0x0000 in program.be16; called from 1 sites (2d5e).
- `sub_0628` -> 0x0628: reads 0x0000 in program.be16; called from 1 sites (2de4).
- `sub_062A` -> 0x062A: reads 0x0000 in program.be16; called from 1 sites (388c).
- `sub_062C` -> 0x062C: reads 0x0000 in program.be16; called from 1 sites (389c).
- `sub_062E` -> 0x062E: reads 0x0000 in program.be16; called from 1 sites (3986).
- `sub_0630` -> 0x0630: reads 0x0000 in program.be16; called from 2 sites (39a4,39f0).
- `sub_0632` -> 0x0632: reads 0x0000 in program.be16; called from 4 sites (3a26,3a81,3ab6,3ade).
- `sub_063A` -> 0x063A: reads 0x0000 in program.be16; called from 1 sites (3d3b).
- `sub_063C` -> 0x063C: reads 0x0000 in program.be16; called from 1 sites (3d79).
- `sub_063E` -> 0x063E: reads 0x0000 in program.be16; called from 1 sites (3ee1).
- `sub_0640` -> 0x0640: reads 0x0000 in program.be16; called from 1 sites (3ef3).
- `sub_064A` -> 0x064A: reads 0x0000 in program.be16; called from 1 sites (3ffa).
- `sub_064E` -> 0x064E: reads 0x0000 in program.be16; called from 1 sites (2b45).
- `sub_0652` -> 0x0652: reads 0x0000 in program.be16; called from 3 sites (4007,4055,40a1).
- `sub_0654` -> 0x0654: reads 0x0000 in program.be16; called from 1 sites (a3a3).
- `sub_0656` -> 0x0656: reads 0x0000 in program.be16; called from 1 sites (a482).
- `sub_065C` -> 0x065C: reads 0x0000 in program.be16; called from 2 sites (a639,a679).
- `sub_065E` -> 0x065E: reads 0x0000 in program.be16; called from 1 sites (a679).
- `sub_0660` -> 0x0660: reads 0x0000 in program.be16; called from 2 sites (a7b7,a7eb).
- `sub_0666` -> 0x0666: reads 0x0000 in program.be16; called from 2 sites (a8d4,a8fe).
- `sub_066E` -> 0x066E: reads 0x0000 in program.be16; called from 2 sites (81f2,82b7).
- `sub_0670` -> 0x0670: reads 0x0000 in program.be16; called from 3 sites (4c41,4cb4,4e96).
- `sub_0672` -> 0x0672: reads 0x0000 in program.be16; called from 3 sites (5395,53ba,53d9).
- `sub_0674` -> 0x0674: reads 0x0000 in program.be16; called from 4 sites (5b26,5bd9,5bf1,5c34).
- `sub_0676` -> 0x0676: reads 0x0000 in program.be16; called from 1 sites (92f4).
- `sub_0678` -> 0x0678: reads 0x0000 in program.be16; called from 3 sites (afbf,b017,b0f5).
- `sub_067A` -> 0x067A: reads 0x0000 in program.be16; called from 1 sites (b050).
- `sub_067C` -> 0x067C: reads 0x0000 in program.be16; called from 2 sites (a87f,a8bf).
- `sub_0682` -> 0x0682: reads 0x0000 in program.be16; called from 1 sites (dfcf).
- `sub_0684` -> 0x0684: reads 0x0000 in program.be16; called from 1 sites (d8f6).
- `sub_0686` -> 0x0686: reads 0x0000 in program.be16; called from 1 sites (b11c).
- `sub_0688` -> 0x0688: reads 0x0000 in program.be16; called from 4 sites (aa2f,aa41,aa56,aa69).
- `sub_068E` -> 0x068E: reads 0x0000 in program.be16; called from 1 sites (a249).
- `sub_0690` -> 0x0690: reads 0x0000 in program.be16; called from 1 sites (af57).
- `sub_0694` -> 0x0694: reads 0x0000 in program.be16; called from 1 sites (c7a4).
- `sub_06A2` -> 0x06A2: reads 0x0000 in program.be16; called from 1 sites (a8fe).
- `sub_06A4` -> 0x06A4: reads 0x0000 in program.be16; called from 1 sites (ab78).
- `sub_06A6` -> 0x06A6: reads 0x0000 in program.be16; called from 1 sites (bac2).
- `sub_06B2` -> 0x06B2: reads 0x0000 in program.be16; called from 1 sites (b461).
- `sub_06B4` -> 0x06B4: reads 0x0000 in program.be16; called from 1 sites (b5ff).
- `sub_06B8` -> 0x06B8: reads 0x0000 in program.be16; called from 1 sites (9ccf).
- `sub_06BC` -> 0x06BC: reads 0x0000 in program.be16; called from 1 sites (3806).
- `sub_06C0` -> 0x06C0: reads 0x0000 in program.be16; called from 1 sites (9ddd).
- `sub_06DA` -> 0x06DA: reads 0x0000 in program.be16; called from 1 sites (c450).
- `sub_06E2` -> 0x06E2: reads 0x0000 in program.be16; called from 3 sites (53ba,53eb,5420).
- `sub_06E4` -> 0x06E4: reads 0x0000 in program.be16; called from 4 sites (5434,544a,546b,5489).
- `sub_06E6` -> 0x06E6: reads 0x0000 in program.be16; called from 3 sites (54a4,54bb,5503).
- `sub_06E8` -> 0x06E8: reads 0x0000 in program.be16; called from 1 sites (5362).
- `sub_06EA` -> 0x06EA: reads 0x0000 in program.be16; called from 1 sites (3475).
- `sub_06F6` -> 0x06F6: reads 0x0000 in program.be16; called from 1 sites (45ff).
- `sub_070A` -> 0x070A: reads 0x0000 in program.be16; called from 1 sites (51d8).
- `sub_072E` -> 0x072E: reads 0x0000 in program.be16; called from 1 sites (294d).
- `sub_0732` -> 0x0732: reads 0x0000 in program.be16; called from 1 sites (28a5).
- `sub_0734` -> 0x0734: reads 0x0000 in program.be16; called from 1 sites (28a5).

## INTERIOR (join into owned span, no C entry; lane-split deferred)
- `frag_AB7E` -> 0xAB7E: rptz zero-fill lane inside ab78_leaf_ab78 (@+0x6, EXPECT words 7-10).
  Refs: 1 site (a843 ccd aneq; delay seats AR2=12694). Evidence: ab78 EXPECT F071 009F 8092 FC00; ccd delay-always convention.
- `frag_9BDC` -> 0x9BDC: mask/merge lane inside 9bc3_frag_9bc3 (@+0x19).
  Refs: 1 site (9c13 bc aeq). Evidence: 9BC3 bound 9BC3-9BF4 owns 0x9BDC; 28d6 interior-join precedent.
