# IAB feature for the ns-3 mmWave module #

Integrated Access and Backhaul (IAB) is a 3GPP Study Item on the possibility of using the same network equipment and resources for both access and backhaul.

This extension of the [ns-3 mmWave module](https://github.com/nyuwireless-unipd/ns3-mmwave "ns-3 mmWave repo") adds wireless relaying capabilities to an ns-3 NetDevice, and the possibility of simulating in-band relaying at mmWave frequencies. This framework has been developed by the University of Padova as part of a project with InterDigital Communications.

---

## Rural Sub-6 GHz Adaptation ##

**This fork adapts the original mmWave IAB implementation for rural 5G deployments:**

- **Sub-6 GHz operation** (3.5 GHz, band n78) instead of 28 GHz mmWave
- **Rural propagation** (RMa scenario) instead of urban UMi-StreetCanyon  
- **Multi-hop cascaded chains** (up to 4 hops) instead of single-hop star topology
- **Long-distance links** (1-3 km per hop) instead of ~80m urban deployment

### Key Modifications

| Aspect | Original (mmWave Urban) | This Fork (Sub-6 Rural) |
|--------|------------------------|------------------------|
| **Frequency** | 28 GHz | 3.5 GHz |
| **Bandwidth** | 100 MHz | 20 MHz |
| **Scenario** | UMi-StreetCanyon | RMa (Rural Macro) |
| **Topology** | Single-hop star | Multi-hop chain |
| **Distance** | ~81 m | 1000-3000 m |
| **Area** | 230×230 m | 5×5 km |

### Research Focus

This adaptation investigates:
- **Coverage extension**: How far can IAB extend rural 5G coverage?
- **QoS trade-offs**: Throughput and latency degradation per hop
- **Viability analysis**: Maximum practical hop count for eMBB services
- **Sub-6 vs mmWave**: Performance comparison in rural deployments

---

## 📚 Relevant papers on IAB ##

### Original mmWave IAB Work

- [M. Polese, M. Giordani, A. Roy, D. Castor, M. Zorzi, "Distributed Path Selection Strategies for Integrated Access and Backhaul at mmWaves", IEEE Global Communications Conference (GLOBECOM), 2018](https://arxiv.org/abs/1805.04351)
- [M. Polese, M. Giordani, A. Roy, S. Goyal, D. Castor, M. Zorzi, "End-to-End Simulation of Integrated Access and Backhaul at mmWaves", IEEE CAMAD, 2018](https://arxiv.org/abs/1808.00376)

### Rural Sub-6 Adaptation (This Work)

- Your paper: "Multi-hop IAB for Rural 5G: Sub-6 GHz Performance Analysis", SBrT 2026 _(in preparation)_

---

## Documentation ##

### Original repository based on mmWave Module Documentation

For the base mmWave module, refer to:

- [End-to-End Simulation of 5G mmWave Networks](https://ieeexplore.ieee.org/document/8344116/)
- [A Framework for End-to-End Evaluation of 5G mmWave Cellular Networks in ns-3](https://arxiv.org/abs/1602.06932)
- [Performance Comparison of Dual Connectivity and Hard Handover for LTE-5G Tight Integration](https://arxiv.org/abs/1607.05425)
- [ns-3 manual](https://www.nsnam.org/docs/manual/html)

---

## Contributing ##

For mmWave-specific questions, please refer to the [original repository](https://github.com/signetlabdei/ns3-mmwave-iab).

---

## Citation ##

If you use this code in your research, please cite:

### Original mmWave IAB Work

```bibtex
@inproceedings{polese2018camad,
  title={End-to-End Simulation of Integrated Access and Backhaul at mmWaves},
  author={Polese, Michele and Giordani, Marco and Roy, Arnab and Goyal, Shivam and Castor, Douglas and Zorzi, Michele},
  booktitle={IEEE CAMAD},
  year={2018}
}
```

### This Rural Adaptation

```bibtex
@inproceedings{yourname2026sbrt,
  title={Multi-hop IAB for Rural 5G: Sub-6 GHz Performance Analysis},
  author={Your Name and Advisors},
  booktitle={Simpósio Brasileiro de Telecomunicações (SBrT)},
  year={2026},
  note={Based on ns3-mmwave-iab by Polese et al.}
}
```

---
## Acknowledgments ##

- **Michele Polese, Marco Giordani, Michele Zorzi** for the original mmWave IAB implementation
- **NYU Wireless and University of Padova** for the mmWave module
- **InterDigital Communications** for supporting the original IAB development
- **ns-3 community** for the excellent network simulator
- **FAPESP** for the funding on this project

---

## Compatibility Notes ##

### Tested Platforms

- ✅ **macOS 14+** (Apple Silicon M1/M2/M3)
- ✅ **Ubuntu 20.04/22.04** (x86_64)
- ⚠️ **Windows WSL2** (not fully tested)

### Known Issues

1. **Python 3.12+ incompatible** - Use Python 3.10 (NS-3.30 limitation with `imp` module)
2. **Clang 17 warnings** - Use `-Wno-error -Wno-deprecated-declarations` flags
3. **std::unary_function deprecated** - Compile with C++11 mode

---

## License ##

This software is licensed under the terms of the **GNU GPLv2**, as like as ns-3 and the original mmWave module. See the [LICENSE](LICENSE) file for more details.

---

## Authors ##

### Original Authors (mmWave IAB)

- **Michele Polese** - University of Padova / NYU Wireless
- **Marco Giordani** - University of Padova
- **Michele Zorzi** - University of Padova

### Rural Adaptation Maintainer

- **João G.** - Federal University of Rio Grande do Norte (UFRN), Brazil

---

<p align="center">
  If this fork helps your research, please star and cite both the original and adapted versions!
</p>