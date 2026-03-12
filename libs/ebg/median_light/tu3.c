
#include "header.h"

void predict_unit3(union Entry* data, double* result) {
  unsigned int tmp;
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7750000000000001332) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.0032160471333742354;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5750608109547740154) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1995315939937592209) ) ) {
                result[0] += -0.002612588389955303;
              } else {
                result[0] += 0.001987160359209293;
              }
            } else {
              result[0] += -0.0030418052761343162;
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += -0.0034133212719122167;
            } else {
              result[0] += -0.002666443927365286;
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6968016071608041928) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05663800000000000778) ) ) {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.08500000000000000611) ) ) {
                result[0] += -0.0026182905840719606;
              } else {
                result[0] += 0.00040526122969719786;
              }
            } else {
              result[0] += 0.0011324435105664842;
            }
          } else {
            result[0] += -0.0028388227749865484;
          }
        }
      }
    } else {
      if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.3050000000000000488) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1650000000000000355) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003897500000000000357) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8274453021105528938) ) ) {
              result[0] += -0.002329214697405369;
            } else {
              result[0] += -0.0037769965919804507;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                result[0] += 0.0019488310033263707;
              } else {
                if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.04446937286580055632) ) ) {
                  result[0] += -0.0006783240550914875;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.04871150000000001173) ) ) {
                    result[0] += -0.0018801216925942161;
                  } else {
                    result[0] += -0.0007597585108894185;
                  }
                }
              }
            } else {
              result[0] += -0.005448687245818392;
            }
          }
        } else {
          result[0] += -0.00108806509335476;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5550000000000001599) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5800027599246232457) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1030960000000000071) ) ) {
              result[0] += 0.00017168168619683202;
            } else {
              result[0] += 0.003496458628986485;
            }
          } else {
            if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3550000000000000377) ) ) {
              result[0] += -0.0009832878431507439;
            } else {
              result[0] += -9.710411322596122e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
                result[0] += -9.433241294136485e-05;
              } else {
                result[0] += 0.0009431784517896709;
              }
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.114862829452247572) ) ) {
                result[0] += 0.001435412129520297;
              } else {
                result[0] += -0.00065219897931412;
              }
            }
          } else {
            result[0] += 0.0032976714402749388;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9050000000000001377) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03403950000000000725) ) ) {
          result[0] += 0.001258963004756289;
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9284011333411857914) ) ) {
            result[0] += 0.002884160567272522;
          } else {
            result[0] += 0.0012586007364140347;
          }
        }
      } else {
        result[0] += 0.0018556006501346503;
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
        result[0] += 0.001899470436987852;
      } else {
        result[0] += 0.002139990507266756;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7750000000000001332) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.003080256699570625;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5750608109547740154) ) ) {
              result[0] += -0.0020239070716461826;
            } else {
              result[0] += -0.002913371817026699;
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += -0.0032692013765866293;
            } else {
              result[0] += -0.002553859265948944;
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6968016071608041928) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05663800000000000778) ) ) {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.08500000000000000611) ) ) {
                result[0] += -0.002507739090424536;
              } else {
                result[0] += 0.00038814997606745723;
              }
            } else {
              result[0] += 0.0010846286032654944;
            }
          } else {
            result[0] += -0.0027189598003097607;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4950000000000000511) ) ) {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1750000000000000167) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.09500000000000001499) ) ) {
              result[0] += -0.0034115907606835643;
            } else {
              result[0] += -0.002808591997077276;
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 0.0012944833208902568;
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.09500000000000001499) ) ) {
                result[0] += -0.0016930754352946097;
              } else {
                result[0] += -0.0006639751198446;
              }
            }
          }
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6050666370100503677) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
              result[0] += 0.0002995224976831312;
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01243050000000000231) ) ) {
                result[0] += -0.0010469249793666347;
              } else {
                result[0] += 0.00028301845841154674;
              }
            }
          } else {
            result[0] += -0.001249684523034274;
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5750000000000000666) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.7760221401809592745) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.005566500000000001135) ) ) {
              result[0] += -1.4039813997999202e-05;
            } else {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
                result[0] += 0.0033557472010852054;
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1627210000000000323) ) ) {
                  result[0] += 0.0006231472132838874;
                } else {
                  result[0] += 0.003626622233617856;
                }
              }
            }
          } else {
            result[0] += -0.0008403288074116062;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
                result[0] += 0.002637764859209988;
              } else {
                result[0] += 0.00011382369220040832;
              }
            } else {
              result[0] += 0.0013288159959123453;
            }
          } else {
            result[0] += 0.003381449370709343;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9550000000000000711) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9050000000000001377) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02804500000000000395) ) ) {
          result[0] += 0.0011319324848177205;
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7290383838442212605) ) ) {
            result[0] += 0.002672060278036592;
          } else {
            result[0] += 0.0012054591209788488;
          }
        }
      } else {
        result[0] += 0.0017572288546352235;
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
        result[0] += 0.0018192695245201594;
      } else {
        result[0] += 0.0020496341700409148;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7750000000000001332) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.0029501997146711752;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4177895562562814469) ) ) {
              result[0] += 0.002390797716858926;
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002803500000000000436) ) ) {
                result[0] += -0.00279036117493757;
              } else {
                result[0] += -0.002280696897793741;
              }
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += -0.0031311666231431078;
            } else {
              result[0] += -0.0024460282413355924;
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6968016071608041928) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05663800000000000778) ) ) {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.08500000000000000611) ) ) {
                result[0] += -0.0024018553875952984;
              } else {
                result[0] += 0.0003717612070459781;
              }
            } else {
              result[0] += 0.001038832574026739;
            }
          } else {
            result[0] += -0.002604157773017558;
          }
        }
      }
    } else {
      if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.29500000000000004) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003726500000000000212) ) ) {
          if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.07500000000000002498) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8254037945979900703) ) ) {
              result[0] += -0.0023548752589164653;
            } else {
              result[0] += -0.003692656342960255;
            }
          } else {
            result[0] += -0.001774358278453673;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 0.00181188927306486;
            } else {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.009795894273113748066) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5458973873869347182) ) ) {
                  result[0] += -0.000579636918436797;
                } else {
                  result[0] += 0.004114558693495878;
                }
              } else {
                result[0] += -0.001319705215196187;
              }
            }
          } else {
            result[0] += -0.005228993378679156;
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5550000000000001599) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5694467910050252657) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1030960000000000071) ) ) {
              result[0] += 0.00018475574238353265;
            } else {
              result[0] += 0.003362356994683919;
            }
          } else {
            result[0] += -0.0004922435490634168;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
                result[0] += -0.00010274306769035648;
              } else {
                result[0] += 0.0008796345110718909;
              }
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.114862829452247572) ) ) {
                result[0] += 0.0013186987479316323;
              } else {
                result[0] += -0.0006807676272202177;
              }
            }
          } else {
            result[0] += 0.0030156604265250534;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9550000000000000711) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9150000000000001465) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02804500000000000395) ) ) {
          result[0] += 0.001210328110942947;
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7290383838442212605) ) ) {
            result[0] += 0.00255219817760316;
          } else {
            result[0] += 0.0011932112351073804;
          }
        }
      } else {
        result[0] += 0.0016830337764639687;
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.008191000000000002099) ) ) {
          result[0] += 0.0017424549171169744;
        } else {
          result[0] += 0.0017424549171169744;
        }
      } else {
        result[0] += 0.0019630929280919683;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7750000000000001332) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.0028256340965540764;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5525538534170856275) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1995315939937592209) ) ) {
                result[0] += -0.0024182969695893852;
              } else {
                result[0] += 0.0032377442432702857;
              }
            } else {
              result[0] += -0.002648770681046204;
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += -0.0029989600800064426;
            } else {
              result[0] += -0.002342750141789098;
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6968016071608041928) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05663800000000000778) ) ) {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.08500000000000000611) ) ) {
                result[0] += -0.002300442388503798;
              } else {
                result[0] += 0.00035606441732786217;
              }
            } else {
              result[0] += 0.0009949701802164802;
            }
          } else {
            result[0] += -0.0024942030058683327;
          }
        }
      }
    } else {
      if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.3150000000000000577) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1650000000000000355) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 0.0010586061750772456;
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01109850000000000246) ) ) {
                result[0] += -0.0019058272637364837;
              } else {
                result[0] += -0.0007547649317970523;
              }
            }
          } else {
            result[0] += -0.00234656387673238;
          }
        } else {
          result[0] += -0.0008967365174021134;
        }
      } else {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6750000000000001554) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
              result[0] += 0.000783192022894947;
            } else {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002990500000000000536) ) ) {
                result[0] += -0.0011617681271931335;
              } else {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3313460023454675718) ) ) {
                  result[0] += 0.001913315686061193;
                } else {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7683067979899498301) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7664523331407036011) ) ) {
                      result[0] += -0.0002170981388114606;
                    } else {
                      result[0] += 0.009007572123110338;
                    }
                  } else {
                    result[0] += -0.0018620312892094286;
                  }
                }
              }
            }
          } else {
            result[0] += 0.002526397640026455;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1324529432504036319) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1475515000000000299) ) ) {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.001774500000000000252) ) ) {
                result[0] += 0.00045878538518716924;
              } else {
                result[0] += 0.0014992767488072952;
              }
            } else {
              result[0] += 0.0033210431791871643;
            }
          } else {
            result[0] += 0.0003079037032561126;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9150000000000001465) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03403950000000000725) ) ) {
          result[0] += 0.0011841774092813994;
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7290383838442212605) ) ) {
            result[0] += 0.0025143454843546092;
          } else {
            result[0] += 0.0012034474880768873;
          }
        }
      } else {
        result[0] += 0.0016268661528590844;
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007451500000000000658) ) ) {
          result[0] += 0.0016688836355822092;
        } else {
          result[0] += 0.0019227001465047752;
        }
      } else {
        result[0] += 0.001880205697511264;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7750000000000001332) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.0027063279844764267;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002803500000000000436) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4389499174623116007) ) ) {
                result[0] += 0.001596433129116954;
              } else {
                result[0] += -0.0025607059355679403;
              }
            } else {
              result[0] += -0.0019282750446248994;
            }
          } else {
            result[0] += -0.0028723356639654613;
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6968016071608041928) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01911900000000000405) ) ) {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.08500000000000000611) ) ) {
                result[0] += -0.0022033113276329953;
              } else {
                result[0] += 0.000341030389626827;
              }
            } else {
              result[0] += -3.956183103588784e-05;
            }
          } else {
            result[0] += -0.0023888908340887536;
          }
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.25500000000000006) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1750000000000000167) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.09500000000000001499) ) ) {
              result[0] += -0.0030606120742914127;
            } else {
              result[0] += -0.002506209286945794;
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 0.0011770503002387995;
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
                result[0] += -0.00013645490133143897;
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                  result[0] += -0.0013697143368206761;
                } else {
                  result[0] += -0.003828609153090415;
                }
              }
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01696050000000000335) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
              result[0] += -0.000438397411954355;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.7099981828132028161) ) ) {
                result[0] += -0.0010769003297102849;
              } else {
                result[0] += -0.0022046409657373992;
              }
            }
          } else {
            result[0] += 9.558831581743664e-05;
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5550000000000001599) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1030960000000000071) ) ) {
            result[0] += -0.00011032459546296672;
          } else {
            result[0] += 0.0017894273524782945;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
                result[0] += -0.00012490989249398416;
              } else {
                result[0] += 0.0008294933525022505;
              }
            } else {
              result[0] += 0.0011325277953761535;
            }
          } else {
            result[0] += 0.0028158610186050917;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9050000000000001377) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01291500000000000113) ) ) {
          result[0] += 0.0009566058647750935;
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6990987027947680454) ) ) {
            result[0] += 0.0023356267972809547;
          } else {
            result[0] += 0.0008268235916078128;
          }
        }
      } else {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9850000000000000977) ) ) {
          result[0] += 0.0024026300400072373;
        } else {
          result[0] += 0.0014236291014869508;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007451500000000000658) ) ) {
          result[0] += 0.0015984187376981733;
        } else {
          result[0] += 0.0018415184112438809;
        }
      } else {
        result[0] += 0.0018008181957997458;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7750000000000001332) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.0025920593074992533;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002803500000000000436) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.468148307738693481) ) ) {
                result[0] += 7.541645389410706e-05;
              } else {
                result[0] += -0.0024525858255652526;
              }
            } else {
              result[0] += -0.0018468579216962407;
            }
          } else {
            result[0] += -0.0027510576821249935;
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6968016071608041928) ) ) {
            result[0] += -0.001917965493446012;
          } else {
            result[0] += -0.0022880252344201213;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.5350000000000001421) ) ) {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1750000000000000167) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.09500000000000001499) ) ) {
              result[0] += -0.002941037038302158;
            } else {
              result[0] += -0.0024062839164769867;
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 0.0011949351016571884;
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.09500000000000001499) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4821784723869347311) ) ) {
                  result[0] += -0.0001302968334447703;
                } else {
                  result[0] += -0.0015632571052297116;
                }
              } else {
                result[0] += -0.00047037214942315645;
              }
            }
          }
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6050666370100503677) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
                result[0] += 0.0003371064710133825;
              } else {
                result[0] += -0.0005493679910354675;
              }
            } else {
              result[0] += 0.00418597790803342;
            }
          } else {
            result[0] += -0.0010924313925669555;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
          if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3477174365476807805) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007303000000000001331) ) ) {
              result[0] += 0.001060105962886868;
            } else {
              result[0] += 0.0033594134521741648;
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5750000000000000666) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.7760221401809592745) ) ) {
                result[0] += 0.00018241459401072103;
              } else {
                result[0] += -0.0006783628289396089;
              }
            } else {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.001812500000000000092) ) ) {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
                  result[0] += 0.002425061900993365;
                } else {
                  result[0] += -0.00020102834696678458;
                }
              } else {
                result[0] += 0.0008633822455204345;
              }
            }
          }
        } else {
          result[0] += 0.0026109404707608625;
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9050000000000001377) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03403950000000000725) ) ) {
          result[0] += 0.0010165195416893874;
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7290383838442212605) ) ) {
            result[0] += 0.002362727523484952;
          } else {
            result[0] += 0.0010596531641140735;
          }
        }
      } else {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9850000000000000977) ) ) {
          result[0] += 0.0023011843329414105;
        } else {
          result[0] += 0.0013635195305605025;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007451500000000000658) ) ) {
          result[0] += 0.0015309290633275965;
        } else {
          result[0] += 0.001763764394107389;
        }
      } else {
        result[0] += 0.0017247826546935702;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7750000000000001332) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.002482615371134826;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002803500000000000436) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.468148307738693481) ) ) {
                result[0] += 7.223216194641199e-05;
              } else {
                result[0] += -0.00234903084661671;
              }
            } else {
              result[0] += -0.0017688784556124692;
            }
          } else {
            result[0] += -0.002634900393197898;
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6968016071608041928) ) ) {
            result[0] += -0.0018369836683748925;
          } else {
            result[0] += -0.0021914184602496375;
          }
        }
      }
    } else {
      if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.29500000000000004) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.09500000000000001499) ) ) {
            result[0] += -0.0028168582938057963;
          } else {
            result[0] += -0.0018864483751519676;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 0.001420530242542943;
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
                result[0] += -0.00013614515904134173;
              } else {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1185261981962025396) ) ) {
                  result[0] += -0.0032774201154315737;
                } else {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.009795894273113748066) ) ) {
                    result[0] += 0.00022888887323796835;
                  } else {
                    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.05500000000000000722) ) ) {
                      result[0] += -0.001585946034112285;
                    } else {
                      result[0] += -0.000978060099393593;
                    }
                  }
                }
              }
            }
          } else {
            result[0] += -0.004433029605990479;
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5350000000000001421) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.7760221401809592745) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02919300000000000367) ) ) {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
                result[0] += 0.0006999055598185778;
              } else {
                if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4950000000000000511) ) ) {
                  result[0] += -0.0009136977194683002;
                } else {
                  result[0] += 0.00013707487174719;
                }
              }
            } else {
              result[0] += 0.0012612683901535903;
            }
          } else {
            result[0] += -0.0008301546055283079;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2070606536698188782) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007599500000000001219) ) ) {
                result[0] += 0.0010111294676763874;
              } else {
                result[0] += 0.0027687583213048075;
              }
            } else {
              result[0] += 0.00047698591780015643;
            }
          } else {
            result[0] += 0.0027691048581799443;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9050000000000001377) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03403950000000000725) ) ) {
          result[0] += 0.000973599266018234;
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7290383838442212605) ) ) {
            result[0] += 0.0022629666113875165;
          } else {
            result[0] += 0.0010149116672177124;
          }
        }
      } else {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9850000000000000977) ) ) {
          result[0] += 0.0022040219451177146;
        } else {
          result[0] += 0.00130594795250958;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007451500000000000658) ) ) {
          result[0] += 0.0014662889902781375;
        } else {
          result[0] += 0.001689293367324916;
        }
      } else {
        result[0] += 0.001651957545115014;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8650000000000001021) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.0023777924614468665;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002803500000000000436) ) ) {
              result[0] += -0.002249848246221958;
            } else {
              result[0] += -0.0016941914989628429;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
                result[0] += -0.002065967881294891;
              } else {
                result[0] += -0.0025236475873205624;
              }
            } else {
              result[0] += -0.002849573723093579;
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6968016071608041928) ) ) {
            result[0] += -0.0017594211206652572;
          } else {
            result[0] += -0.0020988906921474556;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.5950000000000000844) ) ) {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1750000000000000167) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.09500000000000001499) ) ) {
              result[0] += -0.002697922720471127;
            } else {
              result[0] += -0.0022250328477243096;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                result[0] += 0.0013022833830730002;
              } else {
                if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.09500000000000001499) ) ) {
                  result[0] += -0.001292797538946012;
                } else {
                  result[0] += -0.00035948752012841855;
                }
              }
            } else {
              result[0] += -0.00421292153609158;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01660200000000000217) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.3150000000000000577) ) ) {
                result[0] += -0.000940679433682601;
              } else {
                if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.3750000000000000555) ) ) {
                  result[0] += 0.0017542899144645182;
                } else {
                  result[0] += -0.0005365273209118211;
                }
              }
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7210440605025126848) ) ) {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002617500000000000469) ) ) {
                  result[0] += -0.001106563649566094;
                } else {
                  result[0] += -0.0004037599291802891;
                }
              } else {
                result[0] += -0.001598918079246991;
              }
            }
          } else {
            result[0] += 0.00022194917465999834;
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7050000000000000711) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2070606536698188782) ) ) {
              result[0] += 0.0014873335188506805;
            } else {
              result[0] += 0.00014247790094956946;
            }
          } else {
            result[0] += 0.00233371764893759;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9250000000000001554) ) ) {
              result[0] += 0.0024000813949090426;
            } else {
              result[0] += 0.0008321869725816797;
            }
          } else {
            result[0] += 0.0026238809390575625;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9750000000000000888) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9450000000000000622) ) ) {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9850000000000000977) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
            result[0] += 0.0022733092631925076;
          } else {
            result[0] += -0.0011309921039873406;
          }
        } else {
          result[0] += 0.00102054812346177;
        }
      } else {
        result[0] += 0.0013853534544306554;
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
        result[0] += 0.0014043782004749975;
      } else {
        result[0] += 0.0015822073137367301;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8650000000000001021) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.002277395465866748;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002803500000000000436) ) ) {
              result[0] += -0.0021548534104260542;
            } else {
              result[0] += -0.0016226580328630527;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
                result[0] += -0.0019787369847342985;
              } else {
                result[0] += -0.0024170921836097494;
              }
            } else {
              result[0] += -0.002729256813556166;
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6968016071608041928) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01264450000000000122) ) ) {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.07500000000000002498) ) ) {
                result[0] += -0.001915699162174985;
              } else {
                result[0] += -0.0002964759985310873;
              }
            } else {
              result[0] += 1.0573125018056038e-05;
            }
          } else {
            result[0] += -0.002010269703159016;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3450000000000000289) ) ) {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1750000000000000167) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.09500000000000001499) ) ) {
              result[0] += -0.0025743564387417034;
            } else {
              result[0] += -0.0021248133772920155;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                result[0] += 0.0012472973650860123;
              } else {
                if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.09500000000000001499) ) ) {
                  result[0] += -0.0012382120396192237;
                } else {
                  result[0] += -0.00035313341231027056;
                }
              }
            } else {
              result[0] += -0.00403504029889521;
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.468148307738693481) ) ) {
            result[0] += 0.0004149707193400711;
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
              result[0] += -0.0008459846903482282;
            } else {
              result[0] += 0.0019701325584466464;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7050000000000000711) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
              result[0] += 0.0013396821723321297;
            } else {
              result[0] += 0.0001363430960496239;
            }
          } else {
            result[0] += 0.002258404049764047;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9250000000000001554) ) ) {
              result[0] += 0.0022639057562731497;
            } else {
              result[0] += 0.0007970497294611102;
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7290383838442212605) ) ) {
              result[0] += 0.002654669137438126;
            } else {
              result[0] += 0.0005260344217630723;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9750000000000000888) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9450000000000000622) ) ) {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9850000000000000977) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
            result[0] += 0.0021773238381608807;
          } else {
            result[0] += -0.001083238479099458;
          }
        } else {
          result[0] += 0.0009774577498897462;
        }
      } else {
        result[0] += 0.0013268599875295335;
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01594650000000000234) ) ) {
          result[0] += 0.0013450814560063448;
        } else {
          result[0] += 0.0013048534585429117;
        }
      } else {
        result[0] += 0.0015154021306689883;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9050000000000001377) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.0021812375100198882;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002803500000000000436) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4389499174623116007) ) ) {
                result[0] += 0.0017087718844311294;
              } else {
                result[0] += -0.002063869520187499;
              }
            } else {
              result[0] += -0.001554144908191833;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
                result[0] += -0.0018951892186732928;
              } else {
                result[0] += -0.002315035844711718;
              }
            } else {
              result[0] += -0.0026140200177927233;
            }
          }
        } else {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1350000000000000366) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7472528898492464267) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01243050000000000231) ) ) {
                result[0] += -0.001822088212780858;
              } else {
                result[0] += -0.00032815305400288525;
              }
            } else {
              result[0] += -0.002065634171571514;
            }
          } else {
            result[0] += 0.0014480787142010767;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6650000000000001465) ) ) {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1750000000000000167) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.09500000000000001499) ) ) {
              result[0] += -0.0024753124649391734;
            } else {
              result[0] += -0.0020413702702252534;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                result[0] += 0.0011946330093526964;
              } else {
                if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.09500000000000001499) ) ) {
                  result[0] += -0.0011859312915369223;
                } else {
                  result[0] += -0.00032939868699248916;
                }
              }
            } else {
              result[0] += -0.0038646697011150842;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.06607900000000001273) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7210440605025126848) ) ) {
              result[0] += -0.00033825557441247037;
            } else {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0002825000000000000362) ) ) {
                result[0] += -0.00031073447571677805;
              } else {
                result[0] += -0.001445848372116711;
              }
            }
          } else {
            result[0] += 0.0010199358309429464;
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7250000000000000888) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4656778782160804764) ) ) {
            result[0] += 0.001513984221316329;
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
              result[0] += 0.0002641089617502821;
            } else {
              result[0] += 0.002212469309400051;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01291500000000000113) ) ) {
            result[0] += 0.0007633960782433108;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6990987027947680454) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.2059025000000000161) ) ) {
                result[0] += 0.0018572758406116617;
              } else {
                result[0] += 0.0023425429285615362;
              }
            } else {
              result[0] += 0.0004436308524462488;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9550000000000000711) ) ) {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9850000000000000977) ) ) {
          result[0] += 0.0020615540876827644;
        } else {
          result[0] += 0.0011002962168777525;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007451500000000000658) ) ) {
          result[0] += 0.0012882883846247522;
        } else {
          result[0] += 0.0012708362771076478;
        }
      }
    } else {
      result[0] += 0.0014514176478002425;
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9050000000000001377) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.0020891396098863327;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002803500000000000436) ) ) {
              result[0] += -0.0019767272222553567;
            } else {
              result[0] += -0.0014885245977532785;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
                result[0] += -0.0018151690711222944;
              } else {
                result[0] += -0.0022172886076261443;
              }
            } else {
              result[0] += -0.002503648839303503;
            }
          }
        } else {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1350000000000000366) ) ) {
            result[0] += -0.0017243388942161982;
          } else {
            result[0] += 0.0013869368127834719;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6650000000000001465) ) ) {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1750000000000000167) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.09500000000000001499) ) ) {
              result[0] += -0.0023707979042147734;
            } else {
              result[0] += -0.0019551779530570515;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.02500000000000000486) ) ) {
                if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
                  result[0] += -0.0002554713689897317;
                } else {
                  result[0] += 0.002403949417690772;
                }
              } else {
                result[0] += -0.0010471510523047203;
              }
            } else {
              result[0] += -0.0037014926227146535;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01660200000000000217) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
              result[0] += -1.1417727031553075e-05;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.7760221401809592745) ) ) {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002617500000000000469) ) ) {
                  result[0] += -0.0009604882989145399;
                } else {
                  result[0] += -0.00024592896075090095;
                }
              } else {
                result[0] += -0.0014827643750162359;
              }
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7683067979899498301) ) ) {
              result[0] += 0.0005526549075904086;
            } else {
              result[0] += -0.0012452519367385417;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7550000000000001155) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2070606536698188782) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007908500000000000599) ) ) {
                result[0] += 0.0007679639454414506;
              } else {
                result[0] += 0.002680718773769951;
              }
            } else {
              result[0] += 0.000248207379111929;
            }
          } else {
            result[0] += 0.002372936440518887;
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9550000000000000711) ) ) {
            result[0] += 0.0023277641980044054;
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              result[0] += 0.0007311633775615058;
            } else {
              result[0] += 0.0018869689982178735;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9850000000000000977) ) ) {
          result[0] += 0.0019427866116752213;
        } else {
          result[0] += 0.0011199882948674934;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007451500000000000658) ) ) {
          result[0] += 0.0012338932743053295;
        } else {
          result[0] += 0.0011961006909239427;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
        result[0] += 0.0015375415368032534;
      } else {
        result[0] += 0.0013901347673412664;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9050000000000001377) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.0020009303386480932;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002803500000000000436) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4751828078391960308) ) ) {
                result[0] += -0.0006976646111562792;
              } else {
                result[0] += -0.0018932643139428665;
              }
            } else {
              result[0] += -0.0014256749589035538;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.932576353658176371) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6912085704773870409) ) ) {
                result[0] += 0.0023616808291072916;
              } else {
                result[0] += -0.002123668530117684;
              }
            } else {
              result[0] += -0.002123668530117684;
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6968016071608041928) ) ) {
            result[0] += -0.0014765135652779508;
          } else {
            result[0] += -0.00181688505430015;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4350000000000000533) ) ) {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1750000000000000167) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.09500000000000001499) ) ) {
              result[0] += -0.002261043739928036;
            } else {
              result[0] += -0.0018667311748719723;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                result[0] += 0.0011223665667996568;
              } else {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
                  result[0] += -6.481930775364733e-06;
                } else {
                  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1250000000000000278) ) ) {
                    result[0] += -0.0011979187775503785;
                  } else {
                    result[0] += -0.00012343903250402043;
                  }
                }
              }
            } else {
              result[0] += -0.0035452053333452542;
            }
          }
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6050666370100503677) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1113440000000000124) ) ) {
              result[0] += -0.00014325230443428948;
            } else {
              result[0] += 0.002989690361468001;
            }
          } else {
            result[0] += -0.0007930500425495429;
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7250000000000000888) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03105600000000000374) ) ) {
            result[0] += 0.0002658956707656613;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9774026691300493619) ) ) {
              result[0] += 0.001884486639044061;
            } else {
              result[0] += -0.0011585721359002434;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01291500000000000113) ) ) {
            result[0] += 0.0007002916309412307;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6990987027947680454) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.2059025000000000161) ) ) {
                if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9750000000000000888) ) ) {
                  result[0] += 0.0022558491317511307;
                } else {
                  result[0] += 0.001040605059532066;
                }
              } else {
                result[0] += 0.0021639611990355973;
              }
            } else {
              result[0] += 0.0003940277802563954;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9850000000000000977) ) ) {
          result[0] += 0.0018607567701192493;
        } else {
          result[0] += 0.001072699281333834;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007451500000000000658) ) ) {
          result[0] += 0.0011817948764782159;
        } else {
          result[0] += 0.001145598000833407;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
        result[0] += 0.0014726222667754735;
      } else {
        result[0] += 0.0013314394201419538;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9050000000000001377) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.0019164455076031088;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6754021834779359024) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002803500000000000436) ) ) {
              result[0] += -0.0018942907004644073;
            } else {
              result[0] += -0.001238208255907817;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.932576353658176371) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6852090990703517681) ) ) {
                result[0] += 0.00042869204239026745;
              } else {
                result[0] += -0.0020340013520570204;
              }
            } else {
              result[0] += -0.0020340013520570204;
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6968016071608041928) ) ) {
            result[0] += -0.0014141710655473422;
          } else {
            result[0] += -0.001740171125846041;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6650000000000001465) ) ) {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1750000000000000167) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.09500000000000001499) ) ) {
              result[0] += -0.0021752286976441334;
            } else {
              result[0] += -0.0017938063447078439;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.02500000000000000486) ) ) {
                result[0] += 0.000218915344053331;
              } else {
                result[0] += -0.0009677434952012636;
              }
            } else {
              result[0] += -0.0033955169269963264;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.06607900000000001273) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8274453021105528938) ) ) {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
                if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.29500000000000004) ) ) {
                  result[0] += -0.0009311513156922027;
                } else {
                  result[0] += 0.0006655422569731527;
                }
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002682500000000000422) ) ) {
                  result[0] += -0.0009066945709866964;
                } else {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3477174365476807805) ) ) {
                    result[0] += 0.0012896145161368205;
                  } else {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8145641537437187107) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7210440605025126848) ) ) {
                        result[0] += -0.000273031938969325;
                      } else {
                        result[0] += -0.0011917817663580819;
                      }
                    } else {
                      result[0] += 0.006984252986788601;
                    }
                  }
                }
              }
            } else {
              result[0] += -0.002264929811582704;
            }
          } else {
            result[0] += 0.0009455121899791692;
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7250000000000000888) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4656778782160804764) ) ) {
            result[0] += 0.0013723792169920415;
          } else {
            result[0] += 0.0002783247584764046;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01291500000000000113) ) ) {
            result[0] += 0.0006707233751256594;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.3793318106229624509) ) ) {
              result[0] += 0.0018408798735623374;
            } else {
              result[0] += 0.0007951089109728634;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9850000000000000977) ) ) {
          result[0] += 0.0017821904560887732;
        } else {
          result[0] += 0.001027406941168312;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007451500000000000658) ) ) {
          result[0] += 0.0011318962175691078;
        } else {
          result[0] += 0.0010972276744524942;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
        result[0] += 0.0014104440684651481;
      } else {
        result[0] += 0.001275222353368244;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9050000000000001377) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.0018355278605519069;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6754021834779359024) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002803500000000000436) ) ) {
              result[0] += -0.0018143084908453814;
            } else {
              result[0] += -0.00118592766758431;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6276844434422111929) ) ) {
                result[0] += 0.0039739385093766795;
              } else {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
                  result[0] += -0.0015984312048171049;
                } else {
                  result[0] += -0.0019481201710610286;
                }
              }
            } else {
              result[0] += -0.0022223894791694983;
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6968016071608041928) ) ) {
            result[0] += -0.0013544608391422614;
          } else {
            result[0] += -0.0016666962723157603;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6150000000000001021) ) ) {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1750000000000000167) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.09500000000000001499) ) ) {
              result[0] += -0.002083384506242232;
            } else {
              result[0] += -0.0017180668634111302;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                result[0] += 0.001065733922757351;
              } else {
                result[0] += -0.000774320266003633;
              }
            } else {
              result[0] += -0.0032521487805162795;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01660200000000000217) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
              result[0] += -1.3445034089013905e-05;
            } else {
              if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2150000000000000244) ) ) {
                result[0] += -0.0013231874662850307;
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002361500000000000318) ) ) {
                  result[0] += -0.0008564541814872089;
                } else {
                  result[0] += -0.00012408769371800634;
                }
              }
            }
          } else {
            result[0] += 0.00024184067081577405;
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7550000000000001155) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2070606536698188782) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.005458500000000000678) ) ) {
                result[0] += 0.0005496561780592918;
              } else {
                result[0] += 0.0021475279455761428;
              }
            } else {
              result[0] += 0.00017726787870217948;
            }
          } else {
            result[0] += 0.0022332094975185514;
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9550000000000000711) ) ) {
            result[0] += 0.00208287386561326;
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1301345000000000141) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1347820638606622157) ) ) {
                result[0] += 0.0010754392264666502;
              } else {
                result[0] += 0.0003929669211680505;
              }
            } else {
              result[0] += 0.0016688461465239129;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9850000000000000977) ) ) {
          result[0] += 0.0017069414298411275;
        } else {
          result[0] += 0.0009840269692809871;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007451500000000000658) ) ) {
          result[0] += 0.0010841044184970836;
        } else {
          result[0] += 0.001050899677468534;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
        result[0] += 0.0013508912062184858;
      } else {
        result[0] += 0.001221378927143871;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9050000000000001377) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.001758026781088109;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002803500000000000436) ) ) {
              result[0] += -0.0016599540594478563;
            } else {
              result[0] += -0.001263125261059453;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
                result[0] += -0.0015194219846758209;
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  result[0] += -0.0018658651318283193;
                } else {
                  result[0] += -0.0002290695729443169;
                }
              }
            } else {
              result[0] += -0.0021285540287106666;
            }
          }
        } else {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2350000000000000144) ) ) {
            result[0] += -0.001467581446764928;
          } else {
            result[0] += 0.006732419805434184;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4350000000000000533) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1650000000000000355) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01660200000000000217) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                result[0] += 0.0007565533884749053;
              } else {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4992188184422110542) ) ) {
                  result[0] += -0.00037939909768079476;
                } else {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                    result[0] += -0.0030518915750664417;
                  } else {
                    result[0] += -0.001273208626412543;
                  }
                }
              }
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                result[0] += -0.00023016005244139796;
              } else {
                result[0] += -0.007630315650996398;
              }
            }
          } else {
            result[0] += -0.0023017135474914484;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1113440000000000124) ) ) {
            result[0] += -0.00035798472885455456;
          } else {
            result[0] += 0.0011386974235667376;
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7050000000000000711) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7801862323115579256) ) ) {
              result[0] += 0.0004224094570781606;
            } else {
              result[0] += -0.000522830786990109;
            }
          } else {
            result[0] += 0.0017880857526516296;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03403950000000000725) ) ) {
            result[0] += 0.0006400362060080151;
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7290383838442212605) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.2059025000000000161) ) ) {
                result[0] += 0.0015379334821139037;
              } else {
                result[0] += 0.0019570468475554994;
              }
            } else {
              result[0] += 8.4337147975934e-05;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9850000000000000977) ) ) {
          result[0] += 0.001634869626281364;
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.08693186820944626136) ) ) {
            result[0] += 0.0010621301358840634;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5946878489447237071) ) ) {
              result[0] += 9.802141318102946e-05;
            } else {
              result[0] += 0.0006785532826958395;
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007451500000000000658) ) ) {
          result[0] += 0.00103833052179375;
        } else {
          result[0] += 0.001006527777067372;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
        result[0] += 0.0012938528310621413;
      } else {
        result[0] += 0.0011698089197785093;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9050000000000001377) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.0016837980122479418;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002803500000000000436) ) ) {
              result[0] += -0.0015898661930458502;
            } else {
              result[0] += -0.001209792607639164;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
                result[0] += -0.0014552677724166863;
              } else {
                result[0] += -0.00178708312859189;
              }
            } else {
              result[0] += -0.002038680571343209;
            }
          }
        } else {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2350000000000000144) ) ) {
            result[0] += -0.0014056160858626286;
          } else {
            result[0] += 0.006448158360245486;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5550000000000001599) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2850000000000000866) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.468148307738693481) ) ) {
              result[0] += -5.412580798976935e-05;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05256900000000001155) ) ) {
                  if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                    result[0] += 0.0008342680149753589;
                  } else {
                    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.07500000000000002498) ) ) {
                      result[0] += -0.0013771600739071498;
                    } else {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8066186623115578769) ) ) {
                        result[0] += -0.0010677761231766814;
                      } else {
                        result[0] += 0.0009167324337977105;
                      }
                    }
                  }
                } else {
                  result[0] += 2.5502048461209293e-05;
                }
              } else {
                result[0] += -0.007520175274435621;
              }
            }
          } else {
            result[0] += -0.0020901428419839874;
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5694467910050252657) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1030960000000000071) ) ) {
              result[0] += 0.00015470393594926187;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.16821429881140601) ) ) {
                result[0] += 0.002907692482227727;
              } else {
                result[0] += -0.005478591415639858;
              }
            }
          } else {
            result[0] += -0.0003419148437349895;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01291500000000000113) ) ) {
          if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.4314418144595498217) ) ) {
            result[0] += 0.000993177033359963;
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.001851500000000000064) ) ) {
              result[0] += -5.0479460571302656e-05;
            } else {
              result[0] += 0.00046791566735611813;
            }
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6754021834779359024) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
              result[0] += 0.0014861200426282948;
            } else {
              result[0] += 0.0018550584547838479;
            }
          } else {
            result[0] += 3.6733021530419526e-05;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9750000000000000888) ) ) {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9850000000000000977) ) ) {
          result[0] += 0.0015949208435246669;
        } else {
          if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9450000000000000622) ) ) {
            result[0] += 0.0008314829013097623;
          } else {
            result[0] += 0.0009948222869851117;
          }
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01594650000000000234) ) ) {
          result[0] += 0.000994489326021857;
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.08390973343508316418) ) ) {
            result[0] += 0.001240921312050869;
          } else {
            result[0] += 0.000818693966889756;
          }
        }
      }
    } else {
      result[0] += 0.0011204163412196903;
    }
  }
}

