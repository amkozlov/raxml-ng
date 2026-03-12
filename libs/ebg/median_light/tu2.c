
#include "header.h"

void predict_unit2(union Entry* data, double* result) {
  unsigned int tmp;
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6150000000000001021) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0003865000000000000705) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -0.00641342930204371;
          } else {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += -0.006806832659695214;
            } else {
              result[0] += -0.005242936766130555;
            }
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5424744603768845153) ) ) {
              result[0] += -0.0057027805796188375;
            } else {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01243050000000000231) ) ) {
                result[0] += -0.006177481109920451;
              } else {
                result[0] += -0.006762506702695855;
              }
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.714631904321608169) ) ) {
              result[0] += -0.0028020516286904698;
            } else {
              result[0] += -0.004156240966294372;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6800105846231156992) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.679632490452261373) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.06441400000000001291) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4640223026884422453) ) ) {
                result[0] += -0.0022221609139417503;
              } else {
                result[0] += -0.004921381494964273;
              }
            } else {
              result[0] += -0.0008702273337886344;
            }
          } else {
            result[0] += 0.006047024248844221;
          }
        } else {
          result[0] += -0.0053849924121832865;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.25500000000000006) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.005358500000000001283) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2250000000000000333) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
              result[0] += -0.003825858200964372;
            } else {
              result[0] += -0.006958835239098799;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
              result[0] += -0.001622765864408392;
            } else {
              result[0] += -0.002732687518665064;
            }
          }
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
            result[0] += -0.001428505961250471;
          } else {
            result[0] += -0.003138463430008534;
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4350000000000000533) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.08771650000000001668) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5750608109547740154) ) ) {
              result[0] += -0.00026983109920846306;
            } else {
              result[0] += -0.0012126431957954255;
            }
          } else {
            result[0] += 0.0021557353564550185;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004655500000000000783) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6850000000000001643) ) ) {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
                result[0] += 0.0014606135655416239;
              } else {
                result[0] += -0.0009396269662850003;
              }
            } else {
              result[0] += 0.0005026590886396047;
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
              result[0] += 0.0013300470044681186;
            } else {
              result[0] += 0.004972536312648177;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7750000000000001332) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03105600000000000374) ) ) {
          result[0] += 0.0017850390981589109;
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.992027305872230758) ) ) {
            result[0] += 0.00512197461201211;
          } else {
            result[0] += -0.00041638764381956433;
          }
        }
      } else {
        result[0] += 0.003222121671128573;
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9750000000000000888) ) ) {
        result[0] += 0.003733458798463797;
      } else {
        result[0] += 0.004267561156978525;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6350000000000001199) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0003425000000000000852) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -0.006142636521037549;
          } else {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += -0.006519429297320102;
            } else {
              result[0] += -0.005021565427853305;
            }
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5424744603768845153) ) ) {
              result[0] += -0.00539298847320956;
            } else {
              result[0] += -0.0063018223897679;
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.714631904321608169) ) ) {
              result[0] += -0.00268374123384225;
            } else {
              result[0] += -0.003980752940031115;
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5800027599246232457) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1750000000000000167) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02126700000000000465) ) ) {
              result[0] += -0.0042725123550324574;
            } else {
              result[0] += -0.0020706665020610504;
            }
          } else {
            result[0] += 0.0004189653119692863;
          }
        } else {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.115000000000000005) ) ) {
            result[0] += -0.005178706465451287;
          } else {
            result[0] += -0.003966976657981095;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.5350000000000001421) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.29500000000000004) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004225500000000000957) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1650000000000000355) ) ) {
              result[0] += -0.003894377675692443;
            } else {
              result[0] += -0.0025898488136604637;
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7683067979899498301) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.02500000000000000486) ) ) {
                result[0] += 0.002170616986018957;
              } else {
                result[0] += -0.001840797779005049;
              }
            } else {
              result[0] += -0.0034732107432697418;
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5800027599246232457) ) ) {
            result[0] += -0.000362976583754614;
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
              result[0] += -0.0005584571293670194;
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0325310000000000113) ) ) {
                result[0] += -0.002070654240886667;
              } else {
                result[0] += -0.0003530913506487946;
              }
            }
          }
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.2273413669989351737) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02214300000000000296) ) ) {
            result[0] += 0.0007723034888933148;
          } else {
            result[0] += 0.003429744341299579;
          }
        } else {
          if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4450000000000000622) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1155870000000000092) ) ) {
              result[0] += -0.0008760442514129413;
            } else {
              result[0] += 0.002135574719483348;
            }
          } else {
            result[0] += 0.0004511556111693967;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7750000000000001332) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01243050000000000231) ) ) {
          result[0] += 0.0016102531216545238;
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.770367159345256014) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.154253000000000029) ) ) {
              result[0] += 0.003925036828530447;
            } else {
              result[0] += 0.00636514970937841;
            }
          } else {
            result[0] += 0.0013500874611902163;
          }
        }
      } else {
        result[0] += 0.003086074753485452;
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9750000000000000888) ) ) {
        result[0] += 0.003575821808455073;
      } else {
        result[0] += 0.004087372883375222;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6350000000000001199) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -0.005883277362636643;
          } else {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += -0.006244160902386399;
            } else {
              result[0] += -0.004809541001735523;
            }
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5424744603768845153) ) ) {
              result[0] += -0.005096276649138714;
            } else {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.00900100000000000032) ) ) {
                result[0] += -0.00551278887122341;
              } else {
                result[0] += -0.006210894477735238;
              }
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.714631904321608169) ) ) {
              result[0] += -0.0026171827134198996;
            } else {
              result[0] += -0.003748763985471213;
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5556488633165830304) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5528143519346734314) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3197884335317744964) ) ) {
              result[0] += -0.001935572361656112;
            } else {
              result[0] += -0.0037143836090700916;
            }
          } else {
            result[0] += 0.002582221336126981;
          }
        } else {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1550000000000000266) ) ) {
            result[0] += -0.004921127616005196;
          } else {
            result[0] += -0.003422406453767919;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3350000000000000755) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.3050000000000000488) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004225500000000000957) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1650000000000000355) ) ) {
              result[0] += -0.003706102093323061;
            } else {
              result[0] += -0.0025121361431108295;
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.04500000000000000527) ) ) {
                result[0] += 0.0009482699181967601;
              } else {
                result[0] += -0.0017442460945540038;
              }
            } else {
              result[0] += -0.0031205356159284946;
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6050666370100503677) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02264200000000000587) ) ) {
              result[0] += -0.0007510403992680764;
            } else {
              result[0] += 0.0013852793609976767;
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8490362337185931585) ) ) {
              result[0] += -0.0015993109424114235;
            } else {
              result[0] += -0.004364883712127099;
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4350000000000000533) ) ) {
          result[0] += -0.00026824363823359687;
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004655500000000000783) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
              result[0] += 0.00015863293454719833;
            } else {
              result[0] += 0.001778932033969207;
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
              result[0] += 0.001347910156923928;
            } else {
              result[0] += 0.004626274882176724;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9050000000000001377) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7750000000000001332) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.055261500000000012) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.02733191529475900369) ) ) {
            result[0] += 0.002517966214801036;
          } else {
            result[0] += 0.001361643260515957;
          }
        } else {
          result[0] += 0.004696684784207343;
        }
      } else {
        result[0] += 0.0029557721142058823;
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9750000000000000888) ) ) {
        result[0] += 0.003424840689572939;
      } else {
        result[0] += 0.003914792658666788;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6650000000000001465) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -0.005634869067568778;
          } else {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += -0.005980515102896829;
            } else {
              result[0] += -0.004606468835210182;
            }
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5424744603768845153) ) ) {
              result[0] += -0.004881097707950843;
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01243050000000000231) ) ) {
                result[0] += -0.0053883290900721215;
              } else {
                result[0] += -0.005948653279001546;
              }
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.714631904321608169) ) ) {
              result[0] += -0.0025066779971455065;
            } else {
              result[0] += -0.003590480767998463;
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4992188184422110542) ) ) {
          result[0] += -0.0023581689475773724;
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7472528898492464267) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.06276700000000001722) ) ) {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1550000000000000266) ) ) {
                result[0] += -0.004501410534110762;
              } else {
                result[0] += -0.003051784204868011;
              }
            } else {
              result[0] += -0.0008712624973761159;
            }
          } else {
            result[0] += -0.0049012358422755725;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.5350000000000001421) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2150000000000000244) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01291500000000000113) ) ) {
              result[0] += -0.002872285960568549;
            } else {
              result[0] += -0.0012433240662106128;
            }
          } else {
            result[0] += -0.005271857016848463;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03105600000000000374) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2850000000000000866) ) ) {
                result[0] += -0.003504583037559928;
              } else {
                result[0] += 0.00042142041445258286;
              }
            } else {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002617500000000000469) ) ) {
                result[0] += -0.0018354047416329698;
              } else {
                result[0] += -0.0008487621417539074;
              }
            }
          } else {
            result[0] += 0.00024353431078209264;
          }
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.2323027026914575854) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02214300000000000296) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.7550000000000001155) ) ) {
              result[0] += 0.0002888923099553929;
            } else {
              result[0] += 0.0012903993360767032;
            }
          } else {
            result[0] += 0.0033133398851130044;
          }
        } else {
          if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4450000000000000622) ) ) {
            result[0] += -0.0006588875913976349;
          } else {
            result[0] += 0.00042435954541007737;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9050000000000001377) ) ) {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7750000000000001332) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01196600000000000268) ) ) {
          result[0] += 0.0016412591147980707;
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6754021834779359024) ) ) {
            result[0] += 0.004049189507646451;
          } else {
            result[0] += 0.0011488316288195363;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02804500000000000395) ) ) {
          result[0] += 0.0022907732625295518;
        } else {
          result[0] += 0.0043980071691872335;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
        result[0] += 0.003327508510979872;
      } else {
        result[0] += 0.0037494992499182006;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6650000000000001465) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -0.0053969492599977645;
          } else {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += -0.005728001160621561;
            } else {
              result[0] += -0.004411970939036714;
            }
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5424744603768845153) ) ) {
              result[0] += -0.004675004218734768;
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01243050000000000231) ) ) {
                result[0] += -0.005160818884445927;
              } else {
                result[0] += -0.00569748463134078;
              }
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.714631904321608169) ) ) {
              result[0] += -0.0024008390966188137;
            } else {
              result[0] += -0.0034388807071689767;
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4992188184422110542) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.001774500000000000252) ) ) {
            result[0] += -0.0033636593956398804;
          } else {
            result[0] += -0.0002535067349167165;
          }
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7472528898492464267) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.06276700000000001722) ) ) {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1850000000000000255) ) ) {
                result[0] += -0.004254353010656076;
              } else {
                result[0] += -0.001673984212357068;
              }
            } else {
              result[0] += -0.0008344753771726281;
            }
          } else {
            result[0] += -0.0046942920651493565;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3850000000000000644) ) ) {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1850000000000000255) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6050666370100503677) ) ) {
            result[0] += -0.002071928284296227;
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
              result[0] += -0.002943305142561561;
            } else {
              result[0] += -0.005009613642193891;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1030960000000000071) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7210440605025126848) ) ) {
              result[0] += -0.0008284780839695052;
            } else {
              result[0] += -0.001955828827675214;
            }
          } else {
            result[0] += 0.0012658082185289107;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03034700000000000245) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6550000000000001377) ) ) {
            result[0] += -0.00032769447211239487;
          } else {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2070606536698188782) ) ) {
              result[0] += 0.0019549785879937297;
            } else {
              result[0] += 0.0004254077194557896;
            }
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9808239647505231362) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
              result[0] += 0.0024480941622962286;
            } else {
              result[0] += 0.005169661216282173;
            }
          } else {
            result[0] += -0.00047263742403386193;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9050000000000001377) ) ) {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7750000000000001332) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0325310000000000113) ) ) {
          result[0] += 0.0017395966755428464;
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9774026691300493619) ) ) {
            result[0] += 0.00437357013359772;
          } else {
            result[0] += -0.00039868771841535693;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0317295000000000077) ) ) {
          result[0] += 0.0022919745318398196;
        } else {
          result[0] += 0.004306361315790426;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9750000000000000888) ) ) {
        result[0] += 0.00313973777002259;
      } else {
        result[0] += 0.0035911849875403007;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6650000000000001465) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -0.00516907508687821;
          } else {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += -0.0054861490576605205;
            } else {
              result[0] += -0.004225685283729123;
            }
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5424744603768845153) ) ) {
              result[0] += -0.004477612568498083;
            } else {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                result[0] += -0.0054569210209227175;
              } else {
                result[0] += -0.003762166444776449;
              }
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.714631904321608169) ) ) {
              result[0] += -0.0022994690081523275;
            } else {
              result[0] += -0.0032936816215649654;
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4992188184422110542) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.001774500000000000252) ) ) {
            result[0] += -0.003221636362531436;
          } else {
            result[0] += -0.00024280297714238371;
          }
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7472528898492464267) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.06276700000000001722) ) ) {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1850000000000000255) ) ) {
                result[0] += -0.0040747224216402455;
              } else {
                result[0] += -0.0016033039539686056;
              }
            } else {
              result[0] += -0.0007992415112604034;
            }
          } else {
            result[0] += -0.004496086028517462;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3450000000000000289) ) ) {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1650000000000000355) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004225500000000000957) ) ) {
              result[0] += -0.003073273779927908;
            } else {
              result[0] += -0.0017243717032623797;
            }
          } else {
            result[0] += -0.004943961981670643;
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.468148307738693481) ) ) {
            result[0] += 2.3419078871295258e-05;
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8490362337185931585) ) ) {
              result[0] += -0.0013285345244093856;
            } else {
              result[0] += -0.0032909932223871043;
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4950000000000000511) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.08005850000000001854) ) ) {
            result[0] += -0.00012860928316147033;
          } else {
            result[0] += 0.0023842708078703144;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.005458500000000000678) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
              result[0] += 0.0002887290099866719;
            } else {
              result[0] += 0.0016679410555025622;
            }
          } else {
            result[0] += 0.0017527672878125244;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9250000000000001554) ) ) {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7750000000000001332) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01196600000000000268) ) ) {
          result[0] += 0.0014985100021890883;
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6754021834779359024) ) ) {
            result[0] += 0.0037394331541159213;
          } else {
            result[0] += 0.00105686137006765;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
          if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8550000000000000933) ) ) {
            result[0] += 0.0023506022986340756;
          } else {
            result[0] += 0.0026174283525349463;
          }
        } else {
          result[0] += 0.004256671871831147;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
        result[0] += 0.0030529730774791577;
      } else {
        result[0] += 0.003439555192607701;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6850000000000001643) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -0.004950822393649117;
          } else {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += -0.005254508621573572;
            } else {
              result[0] += -0.004047265125690867;
            }
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5424744603768845153) ) ) {
              result[0] += -0.004288555341453364;
            } else {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                result[0] += -0.005226514673648295;
              } else {
                result[0] += -0.0036033173382829177;
              }
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.714631904321608169) ) ) {
              result[0] += -0.0022023790461008835;
            } else {
              result[0] += -0.003154613244251094;
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4992188184422110542) ) ) {
          result[0] += -0.0022265653975721378;
        } else {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.115000000000000005) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
              result[0] += -0.003946600086605902;
            } else {
              result[0] += -0.005450947568706137;
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0997940000000000077) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7106503892964824987) ) ) {
                result[0] += -0.0030980360691366567;
              } else {
                result[0] += -0.003673589886241209;
              }
            } else {
              result[0] += 0.004741611467269775;
            }
          }
        }
      }
    } else {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.5350000000000001421) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.29500000000000004) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004225500000000000957) ) ) {
            result[0] += -0.0029133068627752493;
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
              result[0] += -0.0012316680080461028;
            } else {
              result[0] += -0.002601705196131868;
            }
          }
        } else {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
            result[0] += 0.00024159178977525354;
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002990500000000000536) ) ) {
              result[0] += -0.0018698288019441441;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6644777202348807199) ) ) {
                result[0] += -0.00010176527884314974;
              } else {
                result[0] += -0.001632966011906004;
              }
            }
          }
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.7760221401809592745) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
            if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5250000000000001332) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3477174365476807805) ) ) {
                result[0] += 0.0019249699143107457;
              } else {
                result[0] += 0.00014845950961923484;
              }
            } else {
              result[0] += 0.0012383548886374016;
            }
          } else {
            result[0] += 0.004766360151551482;
          }
        } else {
          if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4850000000000000422) ) ) {
            result[0] += -0.0011546749133196689;
          } else {
            result[0] += 0.0002929568876088409;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9250000000000001554) ) ) {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7750000000000001332) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01130350000000000278) ) ) {
          result[0] += 0.0014782033457850447;
        } else {
          result[0] += 0.0033379409471860273;
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
          result[0] += 0.0023497035989194963;
        } else {
          result[0] += 0.004076943374062172;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
        result[0] += 0.0029240680828105355;
      } else {
        result[0] += 0.003294327628356914;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6850000000000001643) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -0.004741784934731996;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6990533298743719648) ) ) {
              result[0] += -0.0038763783618021882;
            } else {
              result[0] += -0.005032648687450131;
            }
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5450375474120604524) ) ) {
              result[0] += -0.004056557480449974;
            } else {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                result[0] += -0.005005836721683388;
              } else {
                result[0] += -0.003454097053804744;
              }
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.714631904321608169) ) ) {
              result[0] += -0.002109388491650816;
            } else {
              result[0] += -0.003021416719711967;
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
          result[0] += -0.002142021958870459;
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.055261500000000012) ) ) {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1550000000000000266) ) ) {
                result[0] += -0.00394379998218475;
              } else {
                result[0] += -0.002843904188387149;
              }
            } else {
              result[0] += -0.001595617550235381;
            }
          } else {
            result[0] += -0.0051647449921603285;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.5350000000000001421) ) ) {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1850000000000000255) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01243050000000000231) ) ) {
              result[0] += -0.0025338541424024964;
            } else {
              result[0] += -0.0011879133024189509;
            }
          } else {
            result[0] += -0.004566143148515271;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02972700000000000342) ) ) {
            result[0] += -0.0011507115515266774;
          } else {
            result[0] += 0.00023368598022370206;
          }
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.7760221401809592745) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
            if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5250000000000001332) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3477174365476807805) ) ) {
                result[0] += 0.0018436923431549674;
              } else {
                result[0] += 0.00014219113718020207;
              }
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01911900000000000405) ) ) {
                if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9550000000000000711) ) ) {
                  result[0] += 0.0006897798188201651;
                } else {
                  result[0] += 0.0012703720145241862;
                }
              } else {
                result[0] += 0.0026406627009910645;
              }
            }
          } else {
            result[0] += 0.0045651112003383945;
          }
        } else {
          if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4850000000000000422) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1202115000000000128) ) ) {
              result[0] += -0.0013100800944673687;
            } else {
              result[0] += 0.002145266098056327;
            }
          } else {
            result[0] += 0.0002805874349222353;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9250000000000001554) ) ) {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7750000000000001332) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01130350000000000278) ) ) {
          result[0] += 0.001415789498832651;
        } else {
          result[0] += 0.0031970038183344166;
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02804500000000000395) ) ) {
          result[0] += 0.002067070772456009;
        } else {
          result[0] += 0.0037282949188303383;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
        result[0] += 0.0028006058147001973;
      } else {
        result[0] += 0.0031552319748437575;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7050000000000000711) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -0.00454157361736392;
          } else {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7106503892964824987) ) ) {
                result[0] += -0.004296449325697645;
              } else {
                result[0] += -0.004820156295358532;
              }
            } else {
              result[0] += -0.0037127069112585574;
            }
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5450375474120604524) ) ) {
              if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.05751864358971629093) ) ) {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
                  result[0] += 0.002965293079683841;
                } else {
                  result[0] += -0.006248377502976983;
                }
              } else {
                result[0] += -0.0007063411083170994;
              }
            } else {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01243050000000000231) ) ) {
                  result[0] += -0.004535956834386724;
                } else {
                  result[0] += -0.00521670414357519;
                }
              } else {
                result[0] += -0.0033082554918237115;
              }
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.714631904321608169) ) ) {
              result[0] += -0.0020203242564382296;
            } else {
              result[0] += -0.002893844122030319;
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5645244997236181783) ) ) {
          result[0] += -0.002611724880207538;
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
            result[0] += -0.0035726404544818855;
          } else {
            result[0] += -0.004946675127545299;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.5350000000000001421) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.29500000000000004) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004225500000000000957) ) ) {
            result[0] += -0.002701782474436244;
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7683067979899498301) ) ) {
              result[0] += -0.001226914557822044;
            } else {
              result[0] += -0.002712677010850313;
            }
          }
        } else {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
            result[0] += 0.00026866968392287414;
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002617500000000000469) ) ) {
              result[0] += -0.001774965817491797;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.3793318106229624509) ) ) {
                result[0] += 0.00010696471455120982;
              } else {
                result[0] += -0.0013488524342347159;
              }
            }
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5550000000000001599) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.2273413669989351737) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1932010000000000394) ) ) {
              result[0] += 0.00065800160786588;
            } else {
              result[0] += 0.004704243715588351;
            }
          } else {
            result[0] += -0.0002749778321262545;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.04503850000000000908) ) ) {
            result[0] += 0.0009633594049744402;
          } else {
            result[0] += 0.0033605288732895993;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9450000000000000622) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8650000000000001021) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02678800000000000278) ) ) {
          result[0] += 0.0016426375324641827;
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7290383838442212605) ) ) {
            result[0] += 0.003998657563902241;
          } else {
            result[0] += 0.0007672733893586711;
          }
        }
      } else {
        result[0] += 0.0024290858575364395;
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
        result[0] += 0.002682356466130466;
      } else {
        result[0] += 0.003022009325782164;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7050000000000000711) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.03500000000000001027) ) ) {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -0.004349815777358061;
          } else {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6990533298743719648) ) ) {
                result[0] += -0.0038431137478787897;
              } else {
                result[0] += -0.004616635921681293;
              }
            } else {
              result[0] += -0.0035071251819616504;
            }
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.652905739716803768) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5525538534170856275) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1995315939937592209) ) ) {
                result[0] += -0.0029255761653452102;
              } else {
                result[0] += 0.003627530166151348;
              }
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6055650374709939943) ) ) {
                result[0] += -0.0034852307807629558;
              } else {
                result[0] += -0.0003183758016869185;
              }
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6902798926130654378) ) ) {
                result[0] += -0.0001221587666300544;
              } else {
                if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
                  result[0] += -0.004344436150543515;
                } else {
                  result[0] += -0.001532860332879916;
                }
              }
            } else {
              result[0] += -0.00499644041941206;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1550000000000000266) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5800027599246232457) ) ) {
            result[0] += -0.003092101381753869;
          } else {
            result[0] += -0.0038175860976596885;
          }
        } else {
          result[0] += -0.0014087068022219144;
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3350000000000000755) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1550000000000000266) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004133500000000000889) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8274453021105528938) ) ) {
              result[0] += -0.0028942694163527757;
            } else {
              result[0] += -0.004813551210027092;
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7171327966834172285) ) ) {
              result[0] += -0.0010415012659311172;
            } else {
              result[0] += -0.002438802193828417;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1202115000000000128) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.82990551552763836) ) ) {
              result[0] += -0.001048467110055734;
            } else {
              result[0] += -0.0033977432935036527;
            }
          } else {
            result[0] += 0.001727995920059719;
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5350000000000001421) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.005458500000000000678) ) ) {
            result[0] += -0.000257671929975297;
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7210440605025126848) ) ) {
              result[0] += 0.0010377522276716323;
            } else {
              result[0] += -0.0005747926172219414;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
            result[0] += 0.0009382540934659488;
          } else {
            result[0] += 0.004097497868182605;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9450000000000000622) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8550000000000000933) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02678800000000000278) ) ) {
          result[0] += 0.0015732808178810299;
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7290383838442212605) ) ) {
            result[0] += 0.003846912623484281;
          } else {
            result[0] += 0.00070391783789358;
          }
        }
      } else {
        result[0] += 0.0023236939311607717;
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
        result[0] += 0.0025690999331736183;
      } else {
        result[0] += 0.0028944117066278807;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7050000000000000711) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.03500000000000001027) ) ) {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -0.004166154485443622;
          } else {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6990533298743719648) ) ) {
                result[0] += -0.003680846821637086;
              } else {
                result[0] += -0.004421708742905557;
              }
            } else {
              result[0] += -0.0033590446252682914;
            }
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5450375474120604524) ) ) {
              result[0] += -0.003548851742630145;
            } else {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.00900100000000000032) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.173295225808050013) ) ) {
                    result[0] += -0.004219437618874944;
                  } else {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.82990551552763836) ) ) {
                      result[0] += 0.0009057310165877632;
                    } else {
                      result[0] += -0.004555700310389912;
                    }
                  }
                } else {
                  result[0] += -0.00478547684086711;
                }
              } else {
                result[0] += -0.0029880593880925762;
              }
            }
          } else {
            result[0] += -0.002353763538333356;
          }
        }
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1550000000000000266) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
            result[0] += -0.002216313057292469;
          } else {
            result[0] += -0.0036044553288206347;
          }
        } else {
          result[0] += -0.0013492272921765763;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.25500000000000006) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004473500000000000913) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2050000000000000433) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8399823609798996449) ) ) {
              result[0] += -0.0030016034776394504;
            } else {
              result[0] += -0.004685903649631407;
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0003425000000000000852) ) ) {
              result[0] += -0.0008202392294003039;
            } else {
              result[0] += -0.0020180190454447506;
            }
          }
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6828811456281408399) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6735883055778896233) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1202115000000000128) ) ) {
                result[0] += -0.0010758598712612983;
              } else {
                result[0] += 0.0023160068852832636;
              }
            } else {
              result[0] += 0.0080103688800094;
            }
          } else {
            result[0] += -0.0021077225957451106;
          }
        }
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6750000000000001554) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.07584250000000002101) ) ) {
            result[0] += -0.00043691145830928186;
          } else {
            result[0] += 0.0019045807833682224;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1324529432504036319) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01911900000000000405) ) ) {
              result[0] += 0.0010308221527696893;
            } else {
              result[0] += 0.00323054739173028;
            }
          } else {
            result[0] += 0.00030131904165251844;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9550000000000000711) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8550000000000000933) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02678800000000000278) ) ) {
          result[0] += 0.001506852536237404;
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7290383838442212605) ) ) {
            result[0] += 0.0036844852981734602;
          } else {
            result[0] += 0.0006741964735585423;
          }
        }
      } else {
        result[0] += 0.0022284103069256217;
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
        result[0] += 0.002460625405300496;
      } else {
        result[0] += 0.0027722016130099806;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7050000000000000711) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.02500000000000000486) ) ) {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -0.003990247882894021;
          } else {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6990533298743719648) ) ) {
                result[0] += -0.0035254312552767974;
              } else {
                result[0] += -0.004235011930498332;
              }
            } else {
              result[0] += -0.0032172164405699206;
            }
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6413622072216433878) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5673593061306533292) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1995315939937592209) ) ) {
                result[0] += -0.0027604823573597346;
              } else {
                result[0] += 0.0033927151798377807;
              }
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6055650374709939943) ) ) {
                result[0] += -0.0033708852302029484;
              } else {
                result[0] += -0.0002438485442668218;
              }
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6852090990703517681) ) ) {
                result[0] += -0.0003986449807165151;
              } else {
                result[0] += -0.0038923344574288967;
              }
            } else {
              result[0] += -0.004583420729986456;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1550000000000000266) ) ) {
          result[0] += -0.003493120634153249;
        } else {
          result[0] += 0.0006053149421699973;
        }
      }
    } else {
      if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.3150000000000000577) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003726500000000000212) ) ) {
          if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.07500000000000002498) ) ) {
            result[0] += -0.0032768751462157863;
          } else {
            result[0] += -0.0021594860669317834;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 0.002710295387707121;
            } else {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.009795894273113748066) ) ) {
                result[0] += -0.0004007514861158626;
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.04871150000000001173) ) ) {
                  result[0] += -0.0019438621549195609;
                } else {
                  result[0] += -0.0004609737614543302;
                }
              }
            }
          } else {
            result[0] += -0.006556310889022904;
          }
        }
      } else {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4350000000000000533) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5800027599246232457) ) ) {
            result[0] += 9.719117654347939e-05;
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8490362337185931585) ) ) {
              result[0] += -0.000829995297766662;
            } else {
              result[0] += -0.002750975536858449;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.2416736107842603343) ) ) {
              result[0] += 0.001080115367221785;
            } else {
              result[0] += 0.00019496086278897415;
            }
          } else {
            result[0] += 0.0036232602289112694;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9450000000000000622) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8550000000000000933) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02678800000000000278) ) ) {
          result[0] += 0.0014432290409688304;
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7290383838442212605) ) ) {
            result[0] += 0.003528916105237824;
          } else {
            result[0] += 0.0006457300276960609;
          }
        }
      } else {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9850000000000000977) ) ) {
          result[0] += 0.0032254735411976748;
        } else {
          result[0] += 0.0018237603748339673;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
        result[0] += 0.0023567309729874445;
      } else {
        result[0] += 0.002655151568651105;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7150000000000000799) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.02500000000000000486) ) ) {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -0.003821768545206694;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6990533298743719648) ) ) {
              result[0] += -0.0031301975769199037;
            } else {
              result[0] += -0.004056197975554061;
            }
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6413622072216433878) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5673593061306533292) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1995315939937592209) ) ) {
                result[0] += -0.0026439271324928005;
              } else {
                result[0] += 0.0032494653308970077;
              }
            } else {
              result[0] += -0.003030004795012082;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01196600000000000268) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9808239647505231362) ) ) {
                result[0] += -0.003841687618716898;
              } else {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.82990551552763836) ) ) {
                  result[0] += -0.0014768030037234513;
                } else {
                  result[0] += -0.004169821260988554;
                }
              }
            } else {
              result[0] += -0.004150217034644551;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1550000000000000266) ) ) {
          result[0] += -0.0033456313883279405;
        } else {
          result[0] += 0.000579756865694038;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.25500000000000006) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01243050000000000231) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2050000000000000433) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                result[0] += 0.0010977221682632982;
              } else {
                result[0] += -0.0024367409656747335;
              }
            } else {
              result[0] += -0.001254346055828674;
            }
          } else {
            result[0] += -0.0005526991378756342;
          }
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1350000000000000366) ) ) {
              result[0] += -0.002916295370959037;
            } else {
              result[0] += -0.0015719580610715302;
            }
          } else {
            result[0] += -0.004028375812953177;
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4950000000000000511) ) ) {
          if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.00292450000000000045) ) ) {
              result[0] += -0.0005126364830910495;
            } else {
              result[0] += 0.0025713267497326567;
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.107195500000000013) ) ) {
              result[0] += -0.00040674968759051825;
            } else {
              result[0] += 0.0020981795818001414;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01911900000000000405) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
              result[0] += 0.00041661929864935174;
            } else {
              result[0] += 0.001342935469960095;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
              result[0] += 0.0026806362269749715;
            } else {
              result[0] += -0.0001304492933847251;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9450000000000000622) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02678800000000000278) ) ) {
          result[0] += 0.0013949308820955426;
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7290383838442212605) ) ) {
            result[0] += 0.003300340582590517;
          } else {
            result[0] += 0.0009161167720081561;
          }
        }
      } else {
        result[0] += 0.002117783713221602;
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
        result[0] += 0.002257223251891139;
      } else {
        result[0] += 0.002543043701953518;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7250000000000000888) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.02500000000000000486) ) ) {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -0.00366040287265011;
          } else {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6990533298743719648) ) ) {
                result[0] += -0.003244412138056466;
              } else {
                result[0] += -0.0038849340419574393;
              }
            } else {
              result[0] += -0.0029101127017753126;
            }
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6413622072216433878) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5673593061306533292) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1995315939937592209) ) ) {
                result[0] += -0.002532293192635192;
              } else {
                result[0] += 0.003112263888065743;
              }
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6055650374709939943) ) ) {
                result[0] += -0.003100621892258265;
              } else {
                result[0] += -0.00010561737205024555;
              }
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01196600000000000268) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9808239647505231362) ) ) {
                result[0] += -0.0036794809076056085;
              } else {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.82990551552763836) ) ) {
                  result[0] += -0.0014144482830985442;
                } else {
                  result[0] += -0.00399375983700094;
                }
              }
            } else {
              result[0] += -0.003974983355490652;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1550000000000000266) ) ) {
          result[0] += -0.003204369547712012;
        } else {
          result[0] += 0.0005552779221250051;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.25500000000000006) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004473500000000000913) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1550000000000000266) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
              result[0] += -0.0038643585290236205;
            } else {
              result[0] += -0.0015271156779351552;
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
              result[0] += -0.0011229746274184235;
            } else {
              result[0] += -0.0019237607792305111;
            }
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1202115000000000128) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7171327966834172285) ) ) {
                result[0] += -0.0008937192077517275;
              } else {
                result[0] += -0.001949741365072208;
              }
            } else {
              result[0] += 0.0012756588026186463;
            }
          } else {
            result[0] += -0.006252738572354368;
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5550000000000001599) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6050000000000000933) ) ) {
            result[0] += -0.0004314890002544696;
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1475515000000000299) ) ) {
              result[0] += 0.0001944118142683207;
            } else {
              result[0] += 0.0039930771602341795;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.04503850000000000908) ) ) {
            result[0] += 0.0007931133423802225;
          } else {
            result[0] += 0.0029775491563312317;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9450000000000000622) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01291500000000000113) ) ) {
          result[0] += 0.0011880392958540779;
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7290383838442212605) ) ) {
            result[0] += 0.0029376544954382456;
          } else {
            result[0] += 0.0007289073476075016;
          }
        }
      } else {
        result[0] += 0.0020283650084593806;
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
        result[0] += 0.0021619170228918427;
      } else {
        result[0] += 0.002435669340462893;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7250000000000000888) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.02500000000000000486) ) ) {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += -0.003505850506543571;
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5750608109547740154) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1995315939937592209) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02126700000000000465) ) ) {
                  result[0] += -0.0027248587435862877;
                } else {
                  result[0] += -0.0005439003169165738;
                }
              } else {
                result[0] += 0.0017249713784816543;
              }
            } else {
              result[0] += -0.003107424055048442;
            }
          } else {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                result[0] += -0.003720901346857499;
              } else {
                result[0] += -0.002540465313332007;
              }
            } else {
              result[0] += -0.0027872396685754345;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1550000000000000266) ) ) {
          result[0] += -0.003069072173977826;
        } else {
          result[0] += 0.0005318325474772113;
        }
      }
    } else {
      if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.3050000000000000488) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003726500000000000212) ) ) {
            if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.07500000000000002498) ) ) {
              result[0] += -0.002651392238231706;
            } else {
              result[0] += -0.0018225176167405764;
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7240686518592965859) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7171327966834172285) ) ) {
                result[0] += -0.0009654304425271368;
              } else {
                result[0] += -0.002584833127605549;
              }
            } else {
              result[0] += 0.002191584411749507;
            }
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1450000000000000455) ) ) {
            result[0] += -0.0029109673532831523;
          } else {
            result[0] += -0.0013633458310620384;
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4950000000000000511) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5750608109547740154) ) ) {
            result[0] += 0.0002123145466729862;
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8490362337185931585) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.249304608119721216) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.114862829452247572) ) ) {
                  result[0] += -0.0006405265263832503;
                } else {
                  result[0] += -0.0022073063383911476;
                }
              } else {
                result[0] += 0.0010403798105655462;
              }
            } else {
              result[0] += -0.0023934881393945853;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007599500000000001219) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
              result[0] += 0.00023270747543652993;
            } else {
              result[0] += 0.0012260550593929435;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6754021834779359024) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
                result[0] += 0.0017947892053797817;
              } else {
                result[0] += 0.0038223472660828223;
              }
            } else {
              result[0] += 3.0481112470825227e-05;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9550000000000000711) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02678800000000000278) ) ) {
          result[0] += 0.0013682601106367993;
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7290383838442212605) ) ) {
            result[0] += 0.0030345194311635136;
          } else {
            result[0] += 0.0008466592890932028;
          }
        }
      } else {
        result[0] += 0.00200190602886329;
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
        result[0] += 0.002070634887334992;
      } else {
        result[0] += 0.002332828622454944;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7550000000000001155) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.02500000000000000486) ) ) {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += -0.0033578237701833106;
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5750608109547740154) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1995315939937592209) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02126700000000000465) ) ) {
                  result[0] += -0.002609807646540663;
                } else {
                  result[0] += -0.0005209353363310642;
                }
              } else {
                result[0] += 0.001652138300461098;
              }
            } else {
              result[0] += -0.002976219989017206;
            }
          } else {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                result[0] += -0.003563794567299793;
              } else {
                result[0] += -0.002433199818563453;
              }
            } else {
              result[0] += -0.002669554675783245;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1350000000000000366) ) ) {
          result[0] += -0.00294288383836664;
        } else {
          result[0] += -0.00046203261985179573;
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3450000000000000289) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1650000000000000355) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01660200000000000217) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8274453021105528938) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8145641537437187107) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.7099981828132028161) ) ) {
                  if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                    result[0] += 0.0017112702420680832;
                  } else {
                    result[0] += -0.001988180834279238;
                  }
                } else {
                  result[0] += -0.002801972747406316;
                }
              } else {
                result[0] += 0.0007123004510293957;
              }
            } else {
              result[0] += -0.003984759947020492;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
              result[0] += -0.0006441355856774808;
            } else {
              result[0] += -0.006186390924546923;
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.468148307738693481) ) ) {
            result[0] += 0.0002758145725016937;
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
              result[0] += -0.001019419222180467;
            } else {
              result[0] += 0.0018729436394120012;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5550000000000001599) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2750000000000000777) ) ) {
            result[0] += -0.0018409644662473984;
          } else {
            result[0] += 0.00011848124022661867;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
                result[0] += -9.849097520561974e-05;
              } else {
                result[0] += 0.0010741163576673978;
              }
            } else {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2070606536698188782) ) ) {
                result[0] += 0.0024828389838933754;
              } else {
                result[0] += 0.0009827265020995375;
              }
            }
          } else {
            result[0] += 0.003458352685611621;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02678800000000000278) ) ) {
          result[0] += 0.0012989371309343784;
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9284011333411857914) ) ) {
            result[0] += 0.0028952197157308345;
          } else {
            result[0] += 0.0005751780066685212;
          }
        }
      } else {
        result[0] += 0.001937403188631902;
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
        result[0] += 0.0019832069368294594;
      } else {
        result[0] += 0.002234330124921954;
      }
    }
  }
}

