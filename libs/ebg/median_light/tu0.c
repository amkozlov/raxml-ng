
#include "header.h"

void predict_unit0(union Entry* data, double* result) {
  unsigned int tmp;
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4350000000000000533) ) ) {
    if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2050000000000000433) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.07500000000000002498) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.05500000000000000722) ) ) {
          result[0] += 0.5763552689190216;
        } else {
          result[0] += 0.5826886850735379;
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1359205000000000274) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5645244997236181783) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.29500000000000004) ) ) {
              result[0] += 0.5894443288877994;
            } else {
              result[0] += 0.5936666061144208;
            }
          } else {
            result[0] += 0.5873331909036571;
          }
        } else {
          result[0] += 0.5957777453568998;
        }
      }
    } else {
      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01340550000000000248) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3150000000000000577) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2650000000000000688) ) ) {
              result[0] += 0.5919776954754395;
            } else {
              result[0] += 0.5957777453568998;
            }
          } else {
            result[0] += 0.5932443787692596;
          }
        } else {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2850000000000000866) ) ) {
              result[0] += 0.5919776954754395;
            } else {
              result[0] += 0.5987333392897011;
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004384500000000000376) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.5550000000000001599) ) ) {
                result[0] += 0.5957777453568998;
              } else {
                result[0] += 0.5978888845993788;
              }
            } else {
              if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.05463331189772155372) ) ) {
                result[0] += 0.5995777939800233;
              } else {
                result[0] += 0.5974666572542178;
              }
            }
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3450000000000000289) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0997940000000000077) ) ) {
              result[0] += 0.5987333392897011;
            } else {
              result[0] += 0.6063334390526216;
            }
          } else {
            result[0] += 0.5953555180117387;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.7308248862661052003) ) ) {
            result[0] += 0.6038000724649815;
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1155870000000000092) ) ) {
              result[0] += 0.5978888845993788;
            } else {
              result[0] += 0.6027445041020786;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5850000000000000755) ) ) {
      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.00835850000000000308) ) ) {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6850000000000001643) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5150000000000001243) ) ) {
            result[0] += 0.5991555666348622;
          } else {
            result[0] += 0.6016889332225024;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5250000000000001332) ) ) {
            result[0] += 0.6012667058773412;
          } else {
            result[0] += 0.6029556177746592;
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5250000000000001332) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6754021834779359024) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1030960000000000071) ) ) {
              result[0] += 0.6046445271553036;
            } else {
              result[0] += 0.6114001722279019;
            }
          } else {
            result[0] += 0.6008444785321801;
          }
        } else {
          result[0] += 0.6067556663977827;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6850000000000001643) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9650000000000000799) ) ) {
          result[0] += 0.6067556663977827;
        } else {
          result[0] += 0.6067556663977827;
        }
      } else {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8150000000000000577) ) ) {
          result[0] += 0.6109779448827408;
        } else {
          result[0] += 0.6164669054031823;
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4350000000000000533) ) ) {
    if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2050000000000000433) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.07500000000000002498) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.04500000000000000527) ) ) {
          result[0] += -0.02264640776093283;
        } else {
          result[0] += -0.016580406010315036;
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.008191000000000002099) ) ) {
          result[0] += -0.01213200410383874;
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.25500000000000006) ) ) {
              result[0] += -0.007154410290535185;
            } else {
              result[0] += -0.0031104093243243657;
            }
          } else {
            result[0] += -0.010443093464857542;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.009542500000000000634) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3150000000000000577) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2650000000000000688) ) ) {
              result[0] += -0.007683603402568719;
            } else {
              result[0] += -0.0040440021714170955;
            }
          } else {
            result[0] += -0.006470402992184845;
          }
        } else {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2850000000000000866) ) ) {
              result[0] += -0.007683603402568719;
            } else {
              result[0] += -0.0012132016155901506;
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4950000000000000511) ) ) {
              result[0] += -0.0040440021714170955;
            } else {
              result[0] += -0.0023550902740991516;
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.04446937286580055632) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3750000000000000555) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1030960000000000071) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
                result[0] += 0.0019535059897916886;
              } else {
                result[0] += -0.0016354289607512635;
              }
            } else {
              result[0] += 0.006488228191874204;
            }
          } else {
            result[0] += 0.004906284578102173;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3450000000000000289) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.09326150000000001106) ) ) {
              result[0] += -0.004870630509974156;
            } else {
              result[0] += -0.0008594669559333446;
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.08228200000000000791) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7418777389447237525) ) ) {
                result[0] += 9.805196182146504e-05;
              } else {
                result[0] += -0.002848630682602354;
              }
            } else {
              result[0] += 0.003786677915547075;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5850000000000000755) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5250000000000001332) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.008813500000000001888) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6850000000000001643) ) ) {
            result[0] += -0.00038657453536984144;
          } else {
            result[0] += 0.001213199205177598;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6754021834779359024) ) ) {
            result[0] += 0.0052928567030594625;
          } else {
            result[0] += 0.0012310268152795102;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01109850000000000246) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.8350000000000000755) ) ) {
            result[0] += 0.0024085732106658322;
          } else {
            result[0] += 0.003253027900988058;
          }
        } else {
          result[0] += 0.006892627926933405;
        }
      }
    } else {
      if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9550000000000000711) ) ) {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6850000000000001643) ) ) {
          result[0] += 0.006470400581772292;
        } else {
          result[0] += 0.012625541995668444;
        }
      } else {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8150000000000000577) ) ) {
          result[0] += 0.008825490855871443;
        } else {
          result[0] += 0.016193831474945193;
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4350000000000000533) ) ) {
    if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2050000000000000433) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.03500000000000001027) ) ) {
          result[0] += -0.022112441324792884;
        } else {
          result[0] += -0.016724790581023274;
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0997940000000000077) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1350000000000000366) ) ) {
            result[0] += -0.012553351279196304;
          } else {
            result[0] += -0.009086390639257123;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
            result[0] += -0.0010748493207847613;
          } else {
            result[0] += -0.007825343014635144;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.009542500000000000634) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3150000000000000577) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.3150000000000000577) ) ) {
              result[0] += -0.00836069765193554;
            } else {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.3850000000000000644) ) ) {
                result[0] += -0.0022924484296374423;
              } else {
                result[0] += -0.004982875115636398;
              }
            }
          } else {
            result[0] += -0.006197204623891305;
          }
        } else {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2250000000000000333) ) ) {
              result[0] += -0.009892546934221206;
            } else {
              result[0] += -0.0011619768770088537;
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4950000000000000511) ) ) {
              result[0] += -0.003873253178511845;
            } else {
              result[0] += -0.0022556518278624934;
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.04446937286580055632) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3750000000000000555) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1030960000000000071) ) ) {
              result[0] += -0.0008155169279113435;
            } else {
              result[0] += 0.00621427719418872;
            }
          } else {
            result[0] += 0.004699127629340214;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3450000000000000289) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.09326150000000001106) ) ) {
              result[0] += -0.004664978974900858;
            } else {
              result[0] += -0.0008231778762196389;
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.08228200000000000791) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7418777389447237525) ) ) {
                result[0] += 9.391193592045798e-05;
              } else {
                result[0] += -0.002728353590851214;
              }
            } else {
              result[0] += 0.0036267938667435967;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6150000000000001021) ) ) {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5250000000000001332) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.008813500000000001888) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6850000000000001643) ) ) {
            result[0] += -0.0003702522858261218;
          } else {
            result[0] += 0.001161974568370607;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6754021834779359024) ) ) {
            result[0] += 0.005069377606528088;
          } else {
            result[0] += 0.0011790494473062675;
          }
        }
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9650000000000000799) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01531200000000000096) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.8050000000000001599) ) ) {
              result[0] += 0.0023971536921295502;
            } else {
              result[0] += 0.002955227439384031;
            }
          } else {
            result[0] += 0.007446059257307973;
          }
        } else {
          result[0] += 0.004408854488371949;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7350000000000000977) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9650000000000000799) ) ) {
          result[0] += 0.007870178094515339;
        } else {
          result[0] += 0.007186172107632213;
        }
      } else {
        result[0] += 0.01508785563054544;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4650000000000000244) ) ) {
    if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2150000000000000244) ) ) {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.08500000000000000611) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
          result[0] += -0.020756564956445;
        } else {
          result[0] += -0.013156465508108678;
        }
      } else {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.115000000000000005) ) ) {
          result[0] += -0.013239159324390015;
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.00900100000000000032) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
              result[0] += -0.009969421307526522;
            } else {
              result[0] += -0.00940080926408412;
            }
          } else {
            if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
              result[0] += -0.003862108621873477;
            } else {
              result[0] += -0.00840506609192836;
            }
          }
        }
      }
    } else {
      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.009542500000000000634) ) ) {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3150000000000000577) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
            result[0] += -0.005151247570356012;
          } else {
            result[0] += -0.005935541448773277;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4350000000000000533) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2250000000000000333) ) ) {
                result[0] += -0.00947485615298844;
              } else {
                result[0] += -0.0011129149890279882;
              }
            } else {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4750000000000000333) ) ) {
                result[0] += -0.0037097136818784377;
              } else {
                result[0] += -0.002160411948746049;
              }
            }
          } else {
            result[0] += -0.00035461920694883716;
          }
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.2273413669989351737) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4850000000000000422) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2945385430719584252) ) ) {
              result[0] += 0.0018115688852968713;
            } else {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02859250000000000333) ) ) {
                result[0] += -0.003211091223131896;
              } else {
                result[0] += 0.00015696867282872812;
              }
            }
          } else {
            result[0] += 0.003957017295952237;
          }
        } else {
          if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3250000000000000666) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.09326150000000001106) ) ) {
              result[0] += -0.005056782557633132;
            } else {
              result[0] += -0.0005773073495652044;
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.08228200000000000791) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.786764172562814168) ) ) {
                result[0] += -0.0007455966885440985;
              } else {
                result[0] += -0.0036865509046613157;
              }
            } else {
              result[0] += 0.0026182787763004453;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6350000000000001199) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5550000000000001599) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.009542500000000000634) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6850000000000001643) ) ) {
            result[0] += 6.761065488576812e-05;
          } else {
            result[0] += 0.0015351401230279638;
          }
        } else {
          result[0] += 0.004662418993090605;
        }
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9750000000000000888) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01503750000000000052) ) ) {
            result[0] += 0.0032320965241902995;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.992027305872230758) ) ) {
              result[0] += 0.008398348009749963;
            } else {
              result[0] += 0.002487160144147398;
            }
          }
        } else {
          result[0] += 0.005067155108581126;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8050000000000001599) ) ) {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.8950000000000001288) ) ) {
          result[0] += 0.009344266206749156;
        } else {
          result[0] += 0.008398268145707297;
        }
      } else {
        result[0] += 0.014450804500300202;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4650000000000000244) ) ) {
    if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1850000000000000255) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.05500000000000000722) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.03500000000000001027) ) ) {
          result[0] += -0.020302392927414002;
        } else {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2450000000000000233) ) ) {
            result[0] += -0.015564451721936916;
          } else {
            result[0] += -0.006592847044989073;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5645244997236181783) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.008191000000000002099) ) ) {
            result[0] += -0.01009174294621027;
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1202115000000000128) ) ) {
              result[0] += -0.006581452314934272;
            } else {
              result[0] += -0.0006851507417672919;
            }
          }
        } else {
          result[0] += -0.011683632297671274;
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3150000000000000577) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.00835850000000000308) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.3150000000000000577) ) ) {
              result[0] += -0.008055351820401594;
            } else {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.3850000000000000644) ) ) {
                result[0] += -0.0022922776432685024;
              } else {
                result[0] += -0.004712045692539123;
              }
            }
          } else {
            result[0] += -0.006107153764128344;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.04446937286580055632) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1113440000000000124) ) ) {
              result[0] += -0.001984927906007113;
            } else {
              result[0] += 0.005600725161894889;
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
              result[0] += -0.003410043278560771;
            } else {
              result[0] += -0.006041892351805461;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.00900100000000000032) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4350000000000000533) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2250000000000000333) ) ) {
                result[0] += -0.009074801435540555;
              } else {
                result[0] += -0.00106592463009376;
              }
            } else {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4750000000000000333) ) ) {
                result[0] += -0.003553079276579489;
              } else {
                result[0] += -0.002140503908264483;
              }
            }
          } else {
            result[0] += -0.0003396462000401523;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.2273413669989351737) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4050000000000000822) ) ) {
              result[0] += -0.0013302750659937676;
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1030960000000000071) ) ) {
                if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3850000000000000644) ) ) {
                  result[0] += 0.0017112072254484116;
                } else {
                  result[0] += 0.004266030822298151;
                }
              } else {
                result[0] += 0.00806830586091381;
              }
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.08228200000000000791) ) ) {
              result[0] += -0.0014037572366965337;
            } else {
              result[0] += 0.002130827129674412;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6550000000000001377) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5650000000000000577) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.008813500000000001888) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6850000000000001643) ) ) {
            result[0] += 6.475594543160114e-05;
          } else {
            result[0] += 0.0014881498574550946;
          }
        } else {
          result[0] += 0.004823666464698848;
        }
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9650000000000000799) ) ) {
          result[0] += 0.004665848683262406;
        } else {
          result[0] += 0.005017518212921173;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8150000000000000577) ) ) {
        result[0] += 0.00872788938054465;
      } else {
        result[0] += 0.013840651436452493;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4650000000000000244) ) ) {
    if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2150000000000000244) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.05500000000000000722) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.03500000000000001027) ) ) {
          result[0] += -0.01944516956328612;
        } else {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2450000000000000233) ) ) {
            result[0] += -0.014907277382262456;
          } else {
            result[0] += -0.006314478749030476;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.00900100000000000032) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1350000000000000366) ) ) {
            result[0] += -0.012148549727925256;
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
              result[0] += -0.009211521390998524;
            } else {
              result[0] += -0.007968846475427544;
            }
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1202115000000000128) ) ) {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.25500000000000006) ) ) {
                result[0] += -0.006042619393017583;
              } else {
                result[0] += -0.0025347188899813296;
              }
            } else {
              result[0] += 0.0003223010139356814;
            }
          } else {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2450000000000000233) ) ) {
              result[0] += -0.00989060246365692;
            } else {
              result[0] += -0.0068136138784104985;
            }
          }
        }
      }
    } else {
      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01314200000000000264) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3450000000000000289) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7106503892964824987) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.3150000000000000577) ) ) {
                result[0] += -0.006340444589101723;
              } else {
                result[0] += -0.0015083168013648013;
              }
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007751500000000000577) ) ) {
                result[0] += -0.004582609492361008;
              } else {
                result[0] += -0.00275469628727858;
              }
            }
          } else {
            result[0] += -0.006271521389678952;
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2850000000000000866) ) ) {
            result[0] += -0.0042475143591577036;
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4350000000000000533) ) ) {
              result[0] += -0.0016457261587647409;
            } else {
              result[0] += -0.00032530539502999473;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6754021834779359024) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3650000000000000466) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1113440000000000124) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
                result[0] += 0.0029038780924362795;
              } else {
                result[0] += -0.0019171372522735863;
              }
            } else {
              result[0] += 0.005286560012566586;
            }
          } else {
            result[0] += 0.0037312876512102045;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1811070000000000457) ) ) {
            result[0] += -0.0036791926461537503;
          } else {
            result[0] += 0.0013910855259866642;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6550000000000001377) ) ) {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5550000000000001599) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01990600000000000355) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6850000000000001643) ) ) {
            result[0] += 6.202176973178768e-05;
          } else {
            result[0] += 0.0015965618898507498;
          }
        } else {
          result[0] += 0.005464452572254326;
        }
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9650000000000000799) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01531200000000000096) ) ) {
            result[0] += 0.003205584663265711;
          } else {
            result[0] += 0.007806722220023969;
          }
        } else {
          result[0] += 0.004805664671447968;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8250000000000000666) ) ) {
        result[0] += 0.008420170497665679;
      } else {
        result[0] += 0.013678488073163826;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4650000000000000244) ) ) {
    if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1850000000000000255) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.05500000000000000722) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.03500000000000001027) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5259885771356785922) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.001523500000000000331) ) ) {
              result[0] += -0.01946859602498313;
            } else {
              result[0] += -0.011868496655292856;
            }
          } else {
            result[0] += -0.01862414054820044;
          }
        } else {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2450000000000000233) ) ) {
            result[0] += -0.01427785076672516;
          } else {
            result[0] += -0.006047863934938835;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5645244997236181783) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.006138500000000000727) ) ) {
            result[0] += -0.009321291562734108;
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1202115000000000128) ) ) {
              result[0] += -0.006077125153716451;
            } else {
              result[0] += -0.0003142916519692814;
            }
          }
        } else {
          result[0] += -0.010791148300165393;
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3250000000000000666) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02804500000000000395) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7210440605025126848) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.00835850000000000308) ) ) {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
                if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2750000000000000777) ) ) {
                  result[0] += -0.006320073008553177;
                } else {
                  result[0] += -0.0017095761381570572;
                }
              } else {
                result[0] += -0.004820702906947496;
              }
            } else {
              result[0] += -0.003192807229913663;
            }
          } else {
            result[0] += -0.007023275853196429;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.3905483718502500978) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2250000000000000333) ) ) {
              result[0] += -0.003855525103909698;
            } else {
              result[0] += 0.0008335565211835281;
            }
          } else {
            result[0] += -0.003942529271973382;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01340550000000000248) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4050000000000000822) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.4873452877225836199) ) ) {
              result[0] += -0.0016446593882249558;
            } else {
              result[0] += -0.0032651509311268532;
            }
          } else {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.7250000000000000888) ) ) {
              result[0] += -0.00129374258973244;
            } else {
              result[0] += 0.00031150719589347525;
            }
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.7760221401809592745) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1627210000000000323) ) ) {
              result[0] += 0.00256753666825892;
            } else {
              result[0] += 0.01016884480304321;
            }
          } else {
            result[0] += -0.0012871275742316044;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6550000000000001377) ) ) {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5550000000000001599) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01990600000000000355) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6850000000000001643) ) ) {
            result[0] += 5.940303851676574e-05;
          } else {
            result[0] += 0.0015291506167486387;
          }
        } else {
          result[0] += 0.005233728221984262;
        }
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9750000000000000888) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01531200000000000096) ) ) {
            result[0] += 0.003073103890001491;
          } else {
            result[0] += 0.007435509064838191;
          }
        } else {
          result[0] += 0.004743405009886262;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8350000000000000755) ) ) {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7250000000000000888) ) ) {
          result[0] += 0.006648569816819187;
        } else {
          result[0] += 0.009100686625649265;
        }
      } else {
        result[0] += 0.013100944351880221;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4650000000000000244) ) ) {
    if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1650000000000000355) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.05500000000000000722) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.03500000000000001027) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.001523500000000000331) ) ) {
              result[0] += -0.018646577879681256;
            } else {
              result[0] += -0.011789603139166088;
            }
          } else {
            result[0] += -0.017837777656308933;
          }
        } else {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2450000000000000233) ) ) {
            result[0] += -0.013675000289418052;
          } else {
            result[0] += -0.005792506338096367;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5673593061306533292) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.00592850000000000061) ) ) {
            result[0] += -0.00942530371309748;
          } else {
            result[0] += -0.005818138136894662;
          }
        } else {
          result[0] += -0.010757744679336633;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2750000000000000777) ) ) {
        if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.05463331189772155372) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01047950000000000097) ) ) {
            result[0] += -0.005030031499370848;
          } else {
            result[0] += -0.002331808581714682;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1811070000000000457) ) ) {
            result[0] += -0.006376912306421022;
          } else {
            result[0] += 0.0005453645630324886;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.008514500000000002969) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3950000000000000733) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
              result[0] += -0.0018406088345839858;
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7136104594723619021) ) ) {
                if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.7250000000000000888) ) ) {
                  result[0] += -0.0031080151400202974;
                } else {
                  result[0] += 0.00026836168933455976;
                }
              } else {
                result[0] += -0.004304832335779323;
              }
            }
          } else {
            result[0] += -0.0010993862866544928;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.2273413669989351737) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4950000000000000511) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1030960000000000071) ) ) {
                result[0] += -0.00042804049892678175;
              } else {
                result[0] += 0.005872606400839257;
              }
            } else {
              result[0] += 0.0035577871927211548;
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.09326150000000001106) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.786764172562814168) ) ) {
                result[0] += -0.0011828449586650624;
              } else {
                result[0] += -0.004522038209502362;
              }
            } else {
              result[0] += 0.0022968992315309726;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6850000000000001643) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5750000000000000666) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.00835850000000000308) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.7050000000000000711) ) ) {
            result[0] += 5.689487740005111e-05;
          } else {
            result[0] += 0.0015238042769949443;
          }
        } else {
          result[0] += 0.004371907171912501;
        }
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9650000000000000799) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01531200000000000096) ) ) {
            result[0] += 0.003577415362964326;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9808239647505231362) ) ) {
              result[0] += 0.008487684238590905;
            } else {
              result[0] += 0.002386025655000487;
            }
          }
        } else {
          result[0] += 0.0048247037980680115;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8650000000000001021) ) ) {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7650000000000001243) ) ) {
          result[0] += 0.007212303441137556;
        } else {
          result[0] += 0.009169964851105248;
        }
      } else {
        result[0] += 0.012547786129067644;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4650000000000000244) ) ) {
    if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1350000000000000366) ) ) {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.08500000000000000611) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.02500000000000000486) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.001523500000000000331) ) ) {
              result[0] += -0.01785926762139591;
            } else {
              result[0] += -0.011714041355370942;
            }
          } else {
            result[0] += -0.017084617187699384;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007171500000000001658) ) ) {
            result[0] += -0.01311505324344451;
          } else {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.0491948752242571466) ) ) {
              result[0] += -0.005575971763065615;
            } else {
              result[0] += -0.010433346324629233;
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5673593061306533292) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01366150000000000177) ) ) {
            result[0] += -0.009027341237159056;
          } else {
            result[0] += -0.0051239506103026725;
          }
        } else {
          result[0] += -0.011010147975575542;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2750000000000000777) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.009358000000000001734) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.3050000000000000488) ) ) {
              result[0] += -0.009023062547418626;
            } else {
              result[0] += -0.0035916599188696185;
            }
          } else {
            result[0] += -0.006285381918106869;
          }
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
              result[0] += -0.0036563345614340228;
            } else {
              result[0] += 0.002653278011512125;
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
              result[0] += -0.006965458962002307;
            } else {
              result[0] += 0.000406976841409282;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.008514500000000002969) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3950000000000000733) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
              result[0] += -0.0017628932222979517;
            } else {
              result[0] += -0.0031968739628224717;
            }
          } else {
            result[0] += -0.0010529671470736845;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.2273413669989351737) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4950000000000000511) ) ) {
              result[0] += 0.00011115472489503018;
            } else {
              result[0] += 0.003407567545357449;
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.09326150000000001106) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.786764172562814168) ) ) {
                result[0] += -0.0011329019623722743;
              } else {
                result[0] += -0.004331105208622934;
              }
            } else {
              result[0] += 0.0021999177725790533;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6550000000000001377) ) ) {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5350000000000001421) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007171500000000001658) ) ) {
          result[0] += 0.0004767199629664032;
        } else {
          result[0] += 0.003396277292388564;
        }
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9650000000000000799) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.00900100000000000032) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.8050000000000001599) ) ) {
              result[0] += 0.0018816948940287917;
            } else {
              result[0] += 0.0027681082084741303;
            }
          } else {
            result[0] += 0.005745232484315138;
          }
        } else {
          result[0] += 0.004198764071046934;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8050000000000001599) ) ) {
        result[0] += 0.007186867372818609;
      } else {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8850000000000001199) ) ) {
          result[0] += 0.009062389848514903;
        } else {
          result[0] += 0.012017983781316187;
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4650000000000000244) ) ) {
    if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1350000000000000366) ) ) {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.03500000000000001027) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.001851500000000000064) ) ) {
            result[0] += -0.0171051997868304;
          } else {
            result[0] += -0.00912444602834661;
          }
        } else {
          result[0] += -0.016363257243931312;
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5645244997236181783) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01366150000000000177) ) ) {
            result[0] += -0.009774807723149231;
          } else {
            result[0] += -0.00559856238145794;
          }
        } else {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1050000000000000239) ) ) {
            result[0] += -0.013119389352446671;
          } else {
            result[0] += -0.010005291142619176;
          }
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2750000000000000777) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.006546500000000001103) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.3050000000000000488) ) ) {
              result[0] += -0.008642083809627067;
            } else {
              result[0] += -0.0034400100710184614;
            }
          } else {
            result[0] += -0.006184304941075151;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
            result[0] += -0.002652115864978964;
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
                result[0] += -0.00437462017046429;
              } else {
                result[0] += -0.006604854709680651;
              }
            } else {
              result[0] += 0.0005009011872138272;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.008514500000000002969) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3950000000000000733) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
              result[0] += -0.0016884589788065873;
            } else {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4750000000000000333) ) ) {
                result[0] += -0.0037045234070577095;
              } else {
                result[0] += -0.0022304549991102687;
              }
            }
          } else {
            result[0] += -0.0010085079523690125;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.3905483718502500978) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.3950000000000000733) ) ) {
              result[0] += -0.0011718121463373133;
            } else {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
                result[0] += 0.0054157285435064454;
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.08771650000000001668) ) ) {
                  result[0] += 0.0010207032966617247;
                } else {
                  result[0] += 0.005613436106579852;
                }
              }
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.08228200000000000791) ) ) {
              result[0] += -0.002157215581751013;
            } else {
              result[0] += 0.0011145336266898474;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6950000000000000622) ) ) {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5750000000000000666) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.00835850000000000308) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.8050000000000001599) ) ) {
            result[0] += 0.0004919833137351568;
          } else {
            result[0] += 0.001583816614436375;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
            result[0] += 0.0033268579547718396;
          } else {
            result[0] += 0.009238048337047897;
          }
        }
      } else {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6350000000000001199) ) ) {
          result[0] += 0.003731717095489091;
        } else {
          result[0] += 0.005277787640807771;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8650000000000001021) ) ) {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7650000000000001243) ) ) {
          result[0] += 0.0068112301557255815;
        } else {
          result[0] += 0.008400144244861471;
        }
      } else {
        result[0] += 0.011510551158773285;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4650000000000000244) ) ) {
    if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1350000000000000366) ) ) {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.03500000000000001027) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.001523500000000000331) ) ) {
            result[0] += -0.01638297078861477;
          } else {
            result[0] += -0.008777118480290088;
          }
        } else {
          result[0] += -0.015672355118606353;
        }
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1350000000000000366) ) ) {
          result[0] += -0.011533902853548604;
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.107195500000000013) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6968016071608041928) ) ) {
              result[0] += -0.007673177579127479;
            } else {
              result[0] += -0.010260648015208786;
            }
          } else {
            result[0] += -0.0010541205649464403;
          }
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2650000000000000688) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1155870000000000092) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7290383838442212605) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2250000000000000333) ) ) {
              result[0] += -0.0067604569308679216;
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01243050000000000231) ) ) {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0003865000000000000705) ) ) {
                  result[0] += -0.003574919091173079;
                } else {
                  result[0] += -0.005051001952670829;
                }
              } else {
                result[0] += -0.0021926624386551185;
              }
            }
          } else {
            result[0] += -0.007159906665733678;
          }
        } else {
          result[0] += 6.579630440206595e-05;
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01366150000000000177) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3950000000000000733) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
              result[0] += -0.001676265347020499;
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.005141500000000001104) ) ) {
                result[0] += -0.0031397280140878377;
              } else {
                result[0] += -0.0019093189185308958;
              }
            }
          } else {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.7250000000000000888) ) ) {
              if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.05463331189772155372) ) ) {
                result[0] += -0.0005436986030682698;
              } else {
                result[0] += -0.0017925530284496965;
              }
            } else {
              result[0] += 0.0004318148361431271;
            }
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.3793318106229624509) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4950000000000000511) ) ) {
              result[0] += 0.0005367854282567435;
            } else {
              result[0] += 0.003516564967916281;
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.08228200000000000791) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.786764172562814168) ) ) {
                result[0] += -0.0014419668516670882;
              } else {
                result[0] += -0.004349301235607583;
              }
            } else {
              result[0] += 0.0014544844016241318;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6950000000000000622) ) ) {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5550000000000001599) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.00900100000000000032) ) ) {
          result[0] += 0.0008099812308369846;
        } else {
          result[0] += 0.003524883418381786;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6350000000000001199) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007599500000000001219) ) ) {
              result[0] += 0.002052455242847756;
            } else {
              result[0] += 0.005362183652895584;
            }
          } else {
            result[0] += 0.004426793331536385;
          }
        } else {
          result[0] += 0.005054944801898039;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8250000000000000666) ) ) {
        result[0] += 0.00725061883708639;
      } else {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9250000000000001554) ) ) {
          result[0] += 0.008889921536589147;
        } else {
          result[0] += 0.011024543749569498;
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4850000000000000422) ) ) {
    if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2250000000000000333) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.05500000000000000722) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5259885771356785922) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.001340500000000000328) ) ) {
              result[0] += -0.01569123630273247;
            } else {
              result[0] += -0.010041360324586707;
            }
          } else {
            result[0] += -0.0158550802748987;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6413622072216433878) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1155870000000000092) ) ) {
              result[0] += -0.011193920621145421;
            } else {
              result[0] += -0.003467799316984565;
            }
          } else {
            result[0] += -0.01275681003347046;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5645244997236181783) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004225500000000000957) ) ) {
            result[0] += -0.008043851579932109;
          } else {
            result[0] += -0.004445485737661969;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1550000000000000266) ) ) {
            result[0] += -0.009652980293636447;
          } else {
            result[0] += -0.006158821639360296;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3450000000000000289) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6050666370100503677) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02078600000000000239) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.3150000000000000577) ) ) {
                result[0] += -0.004434859063850103;
              } else {
                result[0] += -0.0005335523556475453;
              }
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.006028500000000000872) ) ) {
                result[0] += -0.004144695810840468;
              } else {
                result[0] += -0.002701804689071284;
              }
            }
          } else {
            result[0] += 0.00012972966531774518;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.25500000000000006) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7210440605025126848) ) ) {
                result[0] += -0.005652139148063639;
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
                  result[0] += -0.006241643687240074;
                } else {
                  result[0] += -0.007567705254103791;
                }
              }
            } else {
              result[0] += 3.720199841585771e-05;
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.09030000000000000526) ) ) {
              result[0] += -0.0037676553726435367;
            } else {
              result[0] += 0.0006420023972875735;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01340550000000000248) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.5018975334485012985) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6950000000000000622) ) ) {
              result[0] += -0.0009449825848366786;
            } else {
              result[0] += 0.0006406158433375627;
            }
          } else {
            result[0] += -0.001448875266239341;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6754021834779359024) ) ) {
            result[0] += 0.0030624353469042432;
          } else {
            result[0] += -0.0006380638589428197;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7350000000000000977) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6350000000000001199) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
          if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5350000000000001421) ) ) {
            result[0] += 0.0015121990493092514;
          } else {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
              result[0] += 0.0025917266488895596;
            } else {
              result[0] += 0.004239881833688537;
            }
          }
        } else {
          result[0] += 0.00919167065874353;
        }
      } else {
        result[0] += 0.00518045922003807;
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8850000000000001199) ) ) {
        result[0] += 0.007670109691389977;
      } else {
        result[0] += 0.010559056921747339;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4650000000000000244) ) ) {
    if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.115000000000000005) ) ) {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.03500000000000001027) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
          result[0] += -0.014894224619516056;
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5259885771356785922) ) ) {
            result[0] += -0.00623956495112547;
          } else {
            result[0] += -0.01039973712090834;
          }
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6413622072216433878) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1155870000000000092) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6055650374709939943) ) ) {
              result[0] += -0.009329079125773724;
            } else {
              if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.606193063154585432) ) ) {
                result[0] += 0.004606515643260502;
              } else {
                result[0] += -0.00960217501893205;
              }
            }
          } else {
            result[0] += -0.0024277958636548277;
          }
        } else {
          result[0] += -0.011218912911973331;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2650000000000000688) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.09326150000000001106) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7290383838442212605) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2250000000000000333) ) ) {
              result[0] += -0.006390574545112449;
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01503750000000000052) ) ) {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
                  result[0] += -0.0034014480265720506;
                } else {
                  result[0] += -0.00474733290537245;
                }
              } else {
                result[0] += -0.0020501914699400207;
              }
            }
          } else {
            result[0] += -0.00702444532060467;
          }
        } else {
          result[0] += -0.0006780334906296629;
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01366150000000000177) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3950000000000000733) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
              result[0] += -0.0015271104361913941;
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.005248500000000000561) ) ) {
                result[0] += -0.0028624277089884377;
              } else {
                result[0] += -0.0017169112915941596;
              }
            }
          } else {
            result[0] += -0.000776494665762559;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1243100835431067558) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4550000000000000711) ) ) {
              result[0] += 0.00032415526913726745;
            } else {
              result[0] += 0.0036948138391748883;
            }
          } else {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6750000000000001554) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7683067979899498301) ) ) {
                result[0] += -0.0007893753645637503;
              } else {
                result[0] += -0.004064260815191135;
              }
            } else {
              result[0] += 0.0014930667734040827;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6950000000000000622) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5950000000000000844) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01874250000000000568) ) ) {
          if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5250000000000001332) ) ) {
            result[0] += 0.0006038951191011466;
          } else {
            result[0] += 0.0019173237094908349;
          }
        } else {
          result[0] += 0.004507027703025429;
        }
      } else {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.8950000000000001288) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003447500000000000477) ) ) {
            result[0] += 0.0019928905416822934;
          } else {
            result[0] += 0.005907189686259909;
          }
        } else {
          result[0] += 0.0038282221768646887;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8550000000000000933) ) ) {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7750000000000001332) ) ) {
          result[0] += 0.006087858156309379;
        } else {
          result[0] += 0.007515158358378537;
        }
      } else {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9750000000000000888) ) ) {
          result[0] += 0.008846542203937378;
        } else {
          result[0] += 0.010113224239420716;
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4850000000000000422) ) ) {
    if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2250000000000000333) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0007525000000000000222) ) ) {
            result[0] += -0.014556759299611496;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5259885771356785922) ) ) {
              result[0] += -0.009315115373808136;
            } else {
              result[0] += -0.013290076084437458;
            }
          }
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6968016071608041928) ) ) {
            result[0] += -0.010298831005012407;
          } else {
            result[0] += -0.011735458781440182;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5645244997236181783) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004225500000000000957) ) ) {
            result[0] += -0.007618515285155654;
          } else {
            result[0] += -0.004224409768428668;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1250000000000000278) ) ) {
            result[0] += -0.009301609329094325;
          } else {
            result[0] += -0.006473407259261051;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3250000000000000666) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5705607401507538645) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01626400000000000415) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.3150000000000000577) ) ) {
              result[0] += -0.004867298466072702;
            } else {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
                result[0] += -0.0003618740691494684;
              } else {
                result[0] += -0.002857975439971576;
              }
            }
          } else {
            result[0] += -0.00044829935440150585;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.09326150000000001106) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7290383838442212605) ) ) {
              result[0] += -0.004158666089159511;
            } else {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
                result[0] += -0.005378639246419569;
              } else {
                result[0] += -0.006443170256799307;
              }
            }
          } else {
            result[0] += -0.00048304227741119074;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01340550000000000248) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4350000000000000533) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
              result[0] += -0.0005065661767963378;
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004655500000000000783) ) ) {
                result[0] += -0.0017304314005886178;
              } else {
                result[0] += -0.0008888029109037792;
              }
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.00217550000000000035) ) ) {
              result[0] += -0.0006614669942550518;
            } else {
              result[0] += 0.0007989097008585447;
            }
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1243100835431067558) ) ) {
            result[0] += 0.0032856275403314802;
          } else {
            result[0] += -6.266425838878424e-05;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7450000000000001066) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6350000000000001199) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1475515000000000299) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007303000000000001331) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6850000000000001643) ) ) {
                result[0] += 0.00037575092737791567;
              } else {
                result[0] += 0.0014544825357599958;
              }
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.966590843157139501) ) ) {
                result[0] += 0.0037076517844972273;
              } else {
                result[0] += 0.00019649472260795328;
              }
            }
          } else {
            result[0] += 0.0038992240951260387;
          }
        } else {
          result[0] += 0.009028221413017732;
        }
      } else {
        result[0] += 0.004883321242570536;
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8850000000000001199) ) ) {
        result[0] += 0.007103673696766353;
      } else {
        result[0] += 0.00968621585003082;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4850000000000000422) ) ) {
    if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1350000000000000366) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.02500000000000000486) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5673593061306533292) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0008885000000000000753) ) ) {
              result[0] += -0.01378520650510538;
            } else {
              result[0] += -0.010385335340854866;
            }
          } else {
            result[0] += -0.013942132530135303;
          }
        } else {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1450000000000000455) ) ) {
            result[0] += -0.011161530148517843;
          } else {
            result[0] += -0.005665671569305886;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5645244997236181783) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01366150000000000177) ) ) {
            result[0] += -0.0075003883321469855;
          } else {
            result[0] += -0.00373083027446453;
          }
        } else {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1050000000000000239) ) ) {
            result[0] += -0.00983385746033823;
          } else {
            result[0] += -0.008022788683773995;
          }
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2650000000000000688) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.006546500000000001103) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1750000000000000167) ) ) {
              result[0] += -0.009721917472121545;
            } else {
              result[0] += -0.004046655369905265;
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7210440605025126848) ) ) {
              result[0] += -0.004636488040655986;
            } else {
              result[0] += -0.0064551668761449145;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
              result[0] += -0.0030197282893820016;
            } else {
              result[0] += -0.005300451883712894;
            }
          } else {
            result[0] += 0.0021439773350051716;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01366150000000000177) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4050000000000000822) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
              result[0] += -0.0012869463878909632;
            } else {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.009795894273113748066) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += -0.0018098387340779423;
                } else {
                  result[0] += -0.0001652963836302333;
                }
              } else {
                result[0] += -0.0027248500271515813;
              }
            }
          } else {
            result[0] += -0.0004291829300111733;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1243100835431067558) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.3850000000000000644) ) ) {
              result[0] += -0.0007013647045161075;
            } else {
              result[0] += 0.0033753147976725646;
            }
          } else {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6750000000000001554) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7683067979899498301) ) ) {
                result[0] += -0.0006590979962684012;
              } else {
                result[0] += -0.00389001058726352;
              }
            } else {
              result[0] += 0.001455668684082054;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7450000000000001066) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6350000000000001199) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1475515000000000299) ) ) {
          if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5350000000000001421) ) ) {
            result[0] += 0.001286197154344568;
          } else {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
              result[0] += 0.002242468896952189;
            } else {
              result[0] += 0.0037345880343295267;
            }
          }
        } else {
          result[0] += 0.008647024853605845;
        }
      } else {
        result[0] += 0.004677133869552992;
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8850000000000001199) ) ) {
        result[0] += 0.006803736882136669;
      } else {
        result[0] += 0.009277236939696535;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4850000000000000422) ) ) {
    if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1350000000000000366) ) ) {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
            result[0] += -0.013353457008322234;
          } else {
            result[0] += -0.012562484411655098;
          }
        } else {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.115000000000000005) ) ) {
            result[0] += -0.010891856229414649;
          } else {
            result[0] += -0.005448052166964946;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5645244997236181783) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01366150000000000177) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += -0.002188710320666289;
            } else {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.09500000000000001499) ) ) {
                result[0] += -0.008296817456516895;
              } else {
                result[0] += -0.006431776446205802;
              }
            }
          } else {
            result[0] += -0.004083092072328821;
          }
        } else {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1050000000000000239) ) ) {
            result[0] += -0.009675851748352582;
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.08228200000000000791) ) ) {
              result[0] += -0.00792209101425164;
            } else {
              result[0] += -0.003016244020821744;
            }
          }
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3250000000000000666) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.006546500000000001103) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2050000000000000433) ) ) {
              result[0] += -0.008310362688750263;
            } else {
              result[0] += -0.0029421440514877063;
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7106503892964824987) ) ) {
              result[0] += -0.0038584165262367013;
            } else {
              result[0] += -0.005505695848446323;
            }
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.0286104669690836512) ) ) {
            result[0] += -0.0012473225086385362;
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.09326150000000001106) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
                result[0] += -0.0030407456663618803;
              } else {
                result[0] += -0.005163275959022843;
              }
            } else {
              result[0] += -0.00029730697696423233;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01503750000000000052) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.5018975334485012985) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6850000000000001643) ) ) {
              result[0] += -0.000878314939362077;
            } else {
              result[0] += 0.0007161892386923349;
            }
          } else {
            result[0] += -0.0015816104769344108;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1243100835431067558) ) ) {
            result[0] += 0.0032327996411490876;
          } else {
            result[0] += 7.4286335125811e-05;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7650000000000001243) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6350000000000001199) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
          if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5550000000000001599) ) ) {
            result[0] += 0.0013532328120657293;
          } else {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
              result[0] += 0.002311368663812804;
            } else {
              result[0] += 0.0035769033648491637;
            }
          }
        } else {
          result[0] += 0.00788069692829323;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.001702500000000000237) ) ) {
          result[0] += 0.003129734199147932;
        } else {
          if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6850000000000001643) ) ) {
            result[0] += 0.004519640545491792;
          } else {
            result[0] += 0.005642801675945708;
          }
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9050000000000001377) ) ) {
        result[0] += 0.006646435252438691;
      } else {
        result[0] += 0.008885526253784248;
      }
    }
  }
}

