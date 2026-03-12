
#include "header.h"

void predict_unit1(union Entry* data, double* result) {
  unsigned int tmp;
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4850000000000000422) ) ) {
    if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.115000000000000005) ) ) {
      if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
            result[0] += -0.012789637000486877;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5259885771356785922) ) ) {
              result[0] += -0.009737419336217934;
            } else {
              result[0] += -0.012032061461628255;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004384500000000000376) ) ) {
            result[0] += -0.009334635629722945;
          } else {
            result[0] += -0.004460773629609063;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5645244997236181783) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01366150000000000177) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1350000000000000366) ) ) {
              result[0] += -0.008433644056754822;
            } else {
              result[0] += -0.005705731879089582;
            }
          } else {
            result[0] += -0.004128099568608664;
          }
        } else {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.08500000000000000611) ) ) {
            result[0] += -0.01007218231147834;
          } else {
            result[0] += -0.008228143247771037;
          }
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2650000000000000688) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01314200000000000264) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5511625663567840672) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.29500000000000004) ) ) {
              result[0] += -0.00516103732086867;
            } else {
              result[0] += -0.0023501908218168666;
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1250000000000000278) ) ) {
              result[0] += -0.007632666935449481;
            } else {
              result[0] += -0.005188623136308926;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7593447680904524821) ) ) {
              result[0] += -0.0026044715083888273;
            } else {
              result[0] += -0.005578194474918967;
            }
          } else {
            result[0] += 0.0008746590011571982;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01340550000000000248) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4350000000000000533) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7210440605025126848) ) ) {
              result[0] += -0.001368300877997842;
            } else {
              result[0] += -0.0028095376077943582;
            }
          } else {
            result[0] += -6.3683445720987894e-06;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.3793318106229624509) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4950000000000000511) ) ) {
              result[0] += 0.0005552862225823955;
            } else {
              result[0] += 0.003070687225694433;
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.08228200000000000791) ) ) {
              result[0] += -0.001832771859873294;
            } else {
              result[0] += 0.0017182053950038345;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7650000000000001243) ) ) {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6150000000000001021) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007908500000000000599) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9650000000000000799) ) ) {
              result[0] += 0.0009032153850592592;
            } else {
              result[0] += 0.00252798412673446;
            }
          } else {
            result[0] += 0.0030357050752366863;
          }
        } else {
          result[0] += 0.008741796597191789;
        }
      } else {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6850000000000001643) ) ) {
          result[0] += 0.0034438479763443165;
        } else {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.001702500000000000237) ) ) {
            result[0] += 0.0033100961990950063;
          } else {
            result[0] += 0.005404546931637756;
          }
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9250000000000001554) ) ) {
        result[0] += 0.00654282794071519;
      } else {
        result[0] += 0.008510354679943285;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4850000000000000422) ) ) {
    if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1050000000000000239) ) ) {
      if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0007095000000000001696) ) ) {
            result[0] += -0.01224962303786044;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5259885771356785922) ) ) {
              result[0] += -0.009326278472618275;
            } else {
              result[0] += -0.011524034440360069;
            }
          }
        } else {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0008885000000000000753) ) ) {
            result[0] += -0.010207184705668925;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.606193063154585432) ) ) {
              result[0] += -0.003490938335745426;
            } else {
              result[0] += -0.007174559403965442;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6413622072216433878) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01366150000000000177) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.08500000000000000611) ) ) {
              result[0] += -0.009254540529615437;
            } else {
              result[0] += -0.007297768734200762;
            }
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5012509875628141653) ) ) {
              result[0] += -0.002225117691684249;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6055650374709939943) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.07584250000000002101) ) ) {
                  result[0] += -0.006457622137045537;
                } else {
                  result[0] += -0.0029213438867647205;
                }
              } else {
                result[0] += 0.003837119561735023;
              }
            }
          }
        } else {
          result[0] += -0.009500369624829887;
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2750000000000000777) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01314200000000000264) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6276844434422111929) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.29500000000000004) ) ) {
              result[0] += -0.005169876937431208;
            } else {
              result[0] += -0.0024123328260103206;
            }
          } else {
            result[0] += -0.00558804383049571;
          }
        } else {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4950000000000000511) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
              result[0] += -0.0024269892292502716;
            } else {
              result[0] += -0.004860110861446991;
            }
          } else {
            result[0] += 0.0007269347379509437;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01340550000000000248) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4350000000000000533) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7210440605025126848) ) ) {
              result[0] += -0.0012514418787842095;
            } else {
              result[0] += -0.0025794797896977186;
            }
          } else {
            result[0] += -6.0994553934900315e-06;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.3905483718502500978) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.08771650000000001668) ) ) {
              result[0] += 0.0012953591830966494;
            } else {
              result[0] += 0.005104426123105433;
            }
          } else {
            result[0] += -0.0010713437096478437;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7650000000000001243) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6350000000000001199) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1475515000000000299) ) ) {
          if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5250000000000001332) ) ) {
            result[0] += 0.0008976689480741571;
          } else {
            result[0] += 0.0020769839106850783;
          }
        } else {
          result[0] += 0.007821002687435522;
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01291500000000000113) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9550000000000000711) ) ) {
            result[0] += 0.0031687478970211795;
          } else {
            result[0] += 0.003592562097932038;
          }
        } else {
          result[0] += 0.006968796520144688;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9250000000000001554) ) ) {
        result[0] += 0.006266571590131193;
      } else {
        result[0] += 0.008151023890969548;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4850000000000000422) ) ) {
    if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1050000000000000239) ) ) {
      if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
          result[0] += -0.011732409963157593;
        } else {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0008885000000000000753) ) ) {
            result[0] += -0.009776209044674135;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.606193063154585432) ) ) {
              result[0] += -0.0033435412326143;
            } else {
              result[0] += -0.006871629598085364;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6828811456281408399) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.679632490452261373) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.06441400000000001291) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4992188184422110542) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003120500000000000444) ) ) {
                  result[0] += -0.007096446712997586;
                } else {
                  result[0] += -0.003143999892532338;
                }
              } else {
                result[0] += -0.008185436749035964;
              }
            } else {
              result[0] += -0.0031635038604396373;
            }
          } else {
            result[0] += 0.0011333671158168359;
          }
        } else {
          result[0] += -0.00912936156194956;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2650000000000000688) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01196600000000000268) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.5947576547980821804) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.29500000000000004) ) ) {
              result[0] += -0.005184449240927758;
            } else {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
                result[0] += -0.0013555646158090147;
              } else {
                result[0] += -0.003143133652987393;
              }
            }
          } else {
            result[0] += -0.005629168995341791;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1155870000000000092) ) ) {
            result[0] += -0.0032175854415196514;
          } else {
            result[0] += 0.00036490243651963707;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01366150000000000177) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3850000000000000644) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
              result[0] += -0.0011044225574911662;
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
                result[0] += -0.0009535233246956794;
              } else {
                result[0] += -0.002399662457916839;
              }
            }
          } else {
            result[0] += -0.00040880041620793207;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1243100835431067558) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.3850000000000000644) ) ) {
              result[0] += -0.0008143115965664593;
            } else {
              result[0] += 0.0029119552757726304;
            }
          } else {
            result[0] += -0.0006352845377717429;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7650000000000001243) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6350000000000001199) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01874250000000000568) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9650000000000000799) ) ) {
            result[0] += 0.0011739570026491786;
          } else {
            result[0] += 0.0024770478962773887;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9808239647505231362) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1475515000000000299) ) ) {
              result[0] += 0.0040589382311170315;
            } else {
              result[0] += 0.00828543009106045;
            }
          } else {
            result[0] += -0.0001454034916443332;
          }
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.001702500000000000237) ) ) {
          result[0] += 0.002700491379080798;
        } else {
          result[0] += 0.004631644544036296;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9250000000000001554) ) ) {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8250000000000000666) ) ) {
          result[0] += 0.005658168046849245;
        } else {
          result[0] += 0.006096520184288447;
        }
      } else {
        result[0] += 0.007806865044971208;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4850000000000000422) ) ) {
    if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1050000000000000239) ) ) {
      if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0007525000000000000222) ) ) {
          result[0] += -0.011237035059622688;
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5259885771356785922) ) ) {
            result[0] += -0.006325982971092462;
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.02500000000000000486) ) ) {
              result[0] += -0.010542082826059606;
            } else {
              result[0] += -0.0032023676441723286;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6828811456281408399) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.679632490452261373) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0195175000000000036) ) ) {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.09500000000000001499) ) ) {
                result[0] += -0.008425876484632805;
              } else {
                result[0] += -0.006187446214900605;
              }
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1324529432504036319) ) ) {
                result[0] += -0.002613489467013208;
              } else {
                result[0] += -0.005805383077124983;
              }
            }
          } else {
            result[0] += 0.0010855132113393705;
          }
        } else {
          result[0] += -0.008743894584807819;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2650000000000000688) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01196600000000000268) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6276844434422111929) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.29500000000000004) ) ) {
              result[0] += -0.004779267102741939;
            } else {
              result[0] += -0.0023074565412892884;
            }
          } else {
            result[0] += -0.005267481735505598;
          }
        } else {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.3050000000000000488) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7261071330150754566) ) ) {
              result[0] += -0.0030625278089280103;
            } else {
              result[0] += -0.005369711953198532;
            }
          } else {
            result[0] += -0.0010487056688884952;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01340550000000000248) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4350000000000000533) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7210440605025126848) ) ) {
              result[0] += -0.0011943317217663065;
            } else {
              result[0] += -0.0024988283802782024;
            }
          } else {
            result[0] += 1.1418768442588138e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.3793318106229624509) ) ) {
            result[0] += 0.001692276061640554;
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.09326150000000001106) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.786764172562814168) ) ) {
                result[0] += -0.0010072738294647136;
              } else {
                result[0] += -0.003523953670053987;
              }
            } else {
              result[0] += 0.0019602897607278167;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7750000000000001332) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6350000000000001199) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007908500000000000599) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            result[0] += 0.0009038109308811921;
          } else {
            result[0] += 0.0030881839028238166;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.966590843157139501) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1475515000000000299) ) ) {
              result[0] += 0.00319697165994649;
            } else {
              result[0] += 0.00793559624234625;
            }
          } else {
            result[0] += 0.0004109157552919818;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01291500000000000113) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9550000000000000711) ) ) {
            result[0] += 0.00287933634684069;
          } else {
            result[0] += 0.003297167408866615;
          }
        } else {
          result[0] += 0.006427758217987276;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9250000000000001554) ) ) {
        result[0] += 0.005785072090013536;
      } else {
        result[0] += 0.007477237540416995;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5250000000000001332) ) ) {
    if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2250000000000000333) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.02500000000000000486) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0006695000000000000647) ) ) {
            result[0] += -0.010762576259072832;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5259885771356785922) ) ) {
              result[0] += -0.007247927491433408;
            } else {
              result[0] += -0.010096966837152348;
            }
          }
        } else {
          result[0] += -0.008690244339548065;
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5809002386432161602) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004225500000000000957) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1550000000000000266) ) ) {
              result[0] += -0.006753640953208439;
            } else {
              result[0] += -0.0043691652235022665;
            }
          } else {
            result[0] += -0.003326034496058551;
          }
        } else {
          if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
            result[0] += -0.007762418761585245;
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
              result[0] += -0.005658580153051793;
            } else {
              result[0] += -0.008737023737389441;
            }
          }
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3450000000000000289) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02170000000000000401) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.3150000000000000577) ) ) {
                result[0] += -0.003636221508143646;
              } else {
                result[0] += -0.0004737556048208078;
              }
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007751500000000000577) ) ) {
                result[0] += -0.00309023146651983;
              } else {
                result[0] += -0.00211055958734671;
              }
            }
          } else {
            result[0] += -0.00025019130827266963;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1359205000000000274) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8490362337185931585) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.236061396638114873) ) ) {
                result[0] += -0.0043748783625222176;
              } else {
                result[0] += -0.001982506059291736;
              }
            } else {
              result[0] += -0.006733169396042182;
            }
          } else {
            result[0] += 8.966392033156326e-06;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01503750000000000052) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.7250000000000000888) ) ) {
            result[0] += -0.000668155962242098;
          } else {
            result[0] += 0.00045243534660423604;
          }
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7683067979899498301) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1627210000000000323) ) ) {
              result[0] += 0.0019022464593313564;
            } else {
              result[0] += 0.007817266933157097;
            }
          } else {
            result[0] += -0.0008973003964757113;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8050000000000001599) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6650000000000001465) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01841950000000000184) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9550000000000000711) ) ) {
            result[0] += 0.001409460523481148;
          } else {
            result[0] += 0.0023297949055665172;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9808239647505231362) ) ) {
            result[0] += 0.005128838753469248;
          } else {
            result[0] += 0.0003935657519015498;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02741500000000000534) ) ) {
          result[0] += 0.003862204319357955;
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.992027305872230758) ) ) {
            result[0] += 0.007374726601399608;
          } else {
            result[0] += 0.002377741694092432;
          }
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9350000000000001643) ) ) {
        result[0] += 0.005594846389628503;
      } else {
        result[0] += 0.007161527823749821;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5250000000000001332) ) ) {
    if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1350000000000000366) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.02500000000000000486) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0006695000000000000647) ) ) {
            result[0] += -0.01030815042560235;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5259885771356785922) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.0176232216271788554) ) ) {
                result[0] += -0.008172402776054256;
              } else {
                result[0] += -5.27806136881494e-05;
              }
            } else {
              result[0] += -0.009670644880396984;
            }
          }
        } else {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1450000000000000455) ) ) {
            result[0] += -0.008357331747342888;
          } else {
            result[0] += -0.003419287531597984;
          }
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6126225748691961348) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01366150000000000177) ) ) {
            result[0] += -0.006095999658498007;
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1202115000000000128) ) ) {
              result[0] += -0.003398259132421788;
            } else {
              result[0] += 0.0018632455133164528;
            }
          }
        } else {
          result[0] += -0.007056521914374187;
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3350000000000000755) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.09326150000000001106) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7290383838442212605) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2250000000000000333) ) ) {
              result[0] += -0.004114828547908908;
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
                result[0] += -0.0010892115910716418;
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02170000000000000401) ) ) {
                  if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                    result[0] += -0.0019667193129219726;
                  } else {
                    result[0] += -0.002851970183630085;
                  }
                } else {
                  result[0] += -0.0007877325634538788;
                }
              }
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8490362337185931585) ) ) {
              result[0] += -0.0038384462796399346;
            } else {
              result[0] += -0.006522589017019054;
            }
          }
        } else {
          result[0] += 0.0005910266702179992;
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01503750000000000052) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4350000000000000533) ) ) {
            result[0] += -0.0008597588888194282;
          } else {
            result[0] += 0.0001914220573790212;
          }
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7683067979899498301) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1627210000000000323) ) ) {
              result[0] += 0.0017814492490445734;
            } else {
              result[0] += 0.007487200232020694;
            }
          } else {
            result[0] += -0.0011045310785289379;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7750000000000001332) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6650000000000001465) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01841950000000000184) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9550000000000000711) ) ) {
            result[0] += 0.0013499491892328343;
          } else {
            result[0] += 0.0022314244999784645;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9808239647505231362) ) ) {
            result[0] += 0.004912284949883772;
          } else {
            result[0] += 0.000376948313796754;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01196600000000000268) ) ) {
          result[0] += 0.003024563378207666;
        } else {
          result[0] += 0.006007395137916735;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9250000000000001554) ) ) {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8250000000000000666) ) ) {
          result[0] += 0.00526096307921791;
        } else {
          result[0] += 0.0053586164505743696;
        }
      } else {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9750000000000000888) ) ) {
          result[0] += 0.006068176387329773;
        } else {
          result[0] += 0.0068591482473462535;
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5250000000000001332) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1050000000000000239) ) ) {
      if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0006695000000000000647) ) ) {
          result[0] += -0.00987291171175402;
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5809002386432161602) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += -0.008785615506576734;
            } else {
              result[0] += -0.0037603500830523068;
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.02500000000000000486) ) ) {
              result[0] += -0.009262323419606701;
            } else {
              result[0] += -0.0024820139165622466;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6828811456281408399) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01366150000000000177) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.08500000000000000611) ) ) {
              result[0] += -0.007501857441621573;
            } else {
              result[0] += -0.005796867340041121;
            }
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5012509875628141653) ) ) {
              result[0] += -0.0016013640443641188;
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.679632490452261373) ) ) {
                result[0] += -0.004721020224920986;
              } else {
                result[0] += 0.009719803210753707;
              }
            }
          }
        } else {
          result[0] += -0.007730721504018126;
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3250000000000000666) ) ) {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1850000000000000255) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6050666370100503677) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.3150000000000000577) ) ) {
              result[0] += -0.004107980391530339;
            } else {
              result[0] += -0.0011503446827709962;
            }
          } else {
            result[0] += -0.005032836985544821;
          }
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7290383838442212605) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02859250000000000333) ) ) {
              result[0] += -0.0021658912637534055;
            } else {
              result[0] += 5.6298925326562906e-05;
            }
          } else {
            result[0] += -0.0034196958523510248;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.005358500000000001283) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.7450000000000001066) ) ) {
            result[0] += -0.0010322561421948514;
          } else {
            result[0] += 0.00036358874414760164;
          }
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7210440605025126848) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1627210000000000323) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4950000000000000511) ) ) {
                result[0] += -0.00043241456388719887;
              } else {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3644477482066475482) ) ) {
                  result[0] += 0.0053568052075902125;
                } else {
                  result[0] += 0.0012752611435571425;
                }
              }
            } else {
              result[0] += 0.007662672123405084;
            }
          } else {
            result[0] += -0.0007298656325787768;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7750000000000001332) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6650000000000001465) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01841950000000000184) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9550000000000000711) ) ) {
            result[0] += 0.001292950588647516;
          } else {
            result[0] += 0.0021372075658708566;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9808239647505231362) ) ) {
            result[0] += 0.004704874648775461;
          } else {
            result[0] += 0.00036103251003852455;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01243050000000000231) ) ) {
          result[0] += 0.0029229456306848734;
        } else {
          result[0] += 0.005708121314657346;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9450000000000000622) ) ) {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8650000000000001021) ) ) {
          result[0] += 0.004740309598195422;
        } else {
          result[0] += 0.005455883434573034;
        }
      } else {
        result[0] += 0.006569535975696118;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5250000000000001332) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.09500000000000001499) ) ) {
      if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0006695000000000000647) ) ) {
          result[0] += -0.009456049984097301;
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5809002386432161602) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              result[0] += -0.005241498555892753;
            } else {
              result[0] += -0.010308231416588905;
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.02500000000000000486) ) ) {
              result[0] += -0.008871242423894386;
            } else {
              result[0] += -0.0023772164019552483;
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5645244997236181783) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02126700000000000465) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.09500000000000001499) ) ) {
              result[0] += -0.006481262653501135;
            } else {
              result[0] += -0.00438605531269744;
            }
          } else {
            result[0] += -0.0024083755096082856;
          }
        } else {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.08500000000000000611) ) ) {
            result[0] += -0.007659346446386001;
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.08228200000000000791) ) ) {
              result[0] += -0.0063581393589786294;
            } else {
              result[0] += -0.002410469105412182;
            }
          }
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3250000000000000666) ) ) {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1850000000000000255) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6050666370100503677) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.3150000000000000577) ) ) {
              result[0] += -0.003831657079008991;
            } else {
              result[0] += -0.0011017739383076654;
            }
          } else {
            result[0] += -0.004997778504003927;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1113440000000000124) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7290383838442212605) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.468148307738693481) ) ) {
                result[0] += -0.0007484666995955339;
              } else {
                result[0] += -0.0021699529719223063;
              }
            } else {
              result[0] += -0.0035035499338820922;
            }
          } else {
            result[0] += 0.0013337347788565806;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01503750000000000052) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.7250000000000000888) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.4873452877225836199) ) ) {
              result[0] += -0.0004987314278568998;
            } else {
              result[0] += -0.0013810793584186;
            }
          } else {
            result[0] += 0.00040853581877178476;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1627210000000000323) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7683067979899498301) ) ) {
              result[0] += 0.001563287296561644;
            } else {
              result[0] += -0.0018457030584133885;
            }
          } else {
            result[0] += 0.00667110436867464;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7750000000000001332) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6750000000000001554) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01841950000000000184) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9550000000000000711) ) ) {
            result[0] += 0.00123835862713765;
          } else {
            result[0] += 0.002115036428610961;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9808239647505231362) ) ) {
            result[0] += 0.00463913875405537;
          } else {
            result[0] += 7.80531357617345e-05;
          }
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
          result[0] += 0.0023150632636842403;
        } else {
          result[0] += 0.00418627157663425;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9250000000000001554) ) ) {
        result[0] += 0.004878175674893758;
      } else {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
          result[0] += 0.005869924592605114;
        } else {
          result[0] += 0.006292151937766227;
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5250000000000001332) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.09500000000000001499) ) ) {
      if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0006695000000000000647) ) ) {
          result[0] += -0.009056789315283037;
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5809002386432161602) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.4143094250104821241) ) ) {
                if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                  result[0] += -0.007553554373190541;
                } else {
                  result[0] += -0.0033791694045262263;
                }
              } else {
                result[0] += 0.0027899588296216435;
              }
            } else {
              result[0] += -0.009872989283076391;
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.02500000000000000486) ) ) {
              result[0] += -0.0084966739529859;
            } else {
              result[0] += -0.002276843729205306;
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5800027599246232457) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02126700000000000465) ) ) {
            result[0] += -0.005713958881212608;
          } else {
            result[0] += -0.0025544208335276522;
          }
        } else {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.08500000000000000611) ) ) {
            result[0] += -0.007354650638225715;
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.08228200000000000791) ) ) {
              result[0] += -0.0060349962369511375;
            } else {
              result[0] += -0.001956114763318982;
            }
          }
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.25500000000000006) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.006028500000000000872) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2050000000000000433) ) ) {
            result[0] += -0.005218841555017769;
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
              result[0] += -0.0024689194621880946;
            } else {
              result[0] += -0.0035798402327370514;
            }
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09250981134579591703) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1627210000000000323) ) ) {
              result[0] += -0.0016450448192341517;
            } else {
              result[0] += 0.0038739929304103166;
            }
          } else {
            result[0] += -0.00313436065436475;
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3850000000000000644) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.08771650000000001668) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
              result[0] += -0.0010314498794583309;
            } else {
              result[0] += -0.0026671151186143925;
            }
          } else {
            result[0] += 0.0018503822384918522;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03034700000000000245) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6450000000000001288) ) ) {
              result[0] += -0.0006870853260098313;
            } else {
              result[0] += 0.00039764319415291075;
            }
          } else {
            result[0] += 0.002633119814093272;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8050000000000001599) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7050000000000000711) ) ) {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6150000000000001021) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007599500000000001219) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
              result[0] += 0.0007639586002401924;
            } else {
              result[0] += 0.003586054388924855;
            }
          } else {
            result[0] += 0.002688774016613578;
          }
        } else {
          result[0] += 0.0025493947270989574;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
          result[0] += 0.002253467304854216;
        } else {
          result[0] += 0.004632711482544848;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8850000000000001199) ) ) {
          result[0] += 0.004418880197908403;
        } else {
          result[0] += 0.005023714854754743;
        }
      } else {
        result[0] += 0.006026479823598217;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5250000000000001332) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.09500000000000001499) ) ) {
      if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0006695000000000000647) ) ) {
          result[0] += -0.008674386539767783;
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5259885771356785922) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.0176232216271788554) ) ) {
              result[0] += -0.005676516574616795;
            } else {
              result[0] += 0.0006495299607189862;
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.02500000000000000486) ) ) {
              result[0] += -0.008137920802265353;
            } else {
              result[0] += -0.0023918505266035573;
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5800027599246232457) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004302500000000001636) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.09500000000000001499) ) ) {
              result[0] += -0.006473363966274892;
            } else {
              result[0] += -0.0043862508477342035;
            }
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4821784723869347311) ) ) {
              result[0] += -0.00132617095920607;
            } else {
              result[0] += -0.004580753122984502;
            }
          }
        } else {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.08500000000000000611) ) ) {
            result[0] += -0.007044116880721094;
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.08228200000000000791) ) ) {
              result[0] += -0.005780181950022778;
            } else {
              result[0] += -0.0018735221702178844;
            }
          }
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.25500000000000006) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.006028500000000000872) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1850000000000000255) ) ) {
            result[0] += -0.005096567379394865;
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
              result[0] += -0.002755824044052551;
            } else {
              result[0] += -0.0035195863703714266;
            }
          }
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1155870000000000092) ) ) {
              result[0] += -0.0021324377439062973;
            } else {
              result[0] += 0.001648745388314296;
            }
          } else {
            result[0] += -0.00372721317818906;
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4350000000000000533) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.08771650000000001668) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.4042487501661144456) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.006028500000000000872) ) ) {
                result[0] += -0.0010526484016980474;
              } else {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
                  result[0] += 0.0025998136842652554;
                } else {
                  result[0] += -0.0004732908273458516;
                }
              }
            } else {
              result[0] += -0.0017294347091199236;
            }
          } else {
            result[0] += 0.0022626898634982573;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03105600000000000374) ) ) {
            result[0] += 0.00025044140947354986;
          } else {
            result[0] += 0.00304096611970841;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8050000000000001599) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7050000000000000711) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004748500000000000117) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            result[0] += 0.0008486122521364485;
          } else {
            result[0] += 0.002568052130620351;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
            result[0] += 0.0027671078779429783;
          } else {
            result[0] += 0.007030575965372709;
          }
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
          result[0] += 0.002158319662360757;
        } else {
          result[0] += 0.004437105548983261;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9450000000000000622) ) ) {
        result[0] += 0.004485628178632514;
      } else {
        result[0] += 0.005772025123272818;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5350000000000001421) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.09500000000000001499) ) ) {
      if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0007525000000000000222) ) ) {
          result[0] += -0.00830812987051946;
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6461954822149375) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.02500000000000000486) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4737195465326633492) ) ) {
                result[0] += -0.0038008987480574585;
              } else {
                result[0] += -0.006105404172818899;
              }
            } else {
              result[0] += -0.0011681897370764852;
            }
          } else {
            result[0] += -0.008216542943421676;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5645244997236181783) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02126700000000000465) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.09500000000000001499) ) ) {
              result[0] += -0.005754122026106362;
            } else {
              result[0] += -0.0038439377682411946;
            }
          } else {
            result[0] += -0.00207412911472775;
          }
        } else {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.08500000000000000611) ) ) {
            result[0] += -0.006742459957202621;
          } else {
            result[0] += -0.005471442064762304;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3350000000000000755) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2150000000000000244) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.006028500000000000872) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8274453021105528938) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1350000000000000366) ) ) {
                result[0] += -0.0051328646112298645;
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0005965000000000001334) ) ) {
                  result[0] += -0.003366732766744692;
                } else {
                  result[0] += -0.0036256756036397255;
                }
              }
            } else {
              result[0] += -0.006655124039256468;
            }
          } else {
            if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09250981134579591703) ) ) {
              result[0] += -0.0013926201936329604;
            } else {
              result[0] += -0.0032906669119562248;
            }
          }
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02859250000000000333) ) ) {
              result[0] += -0.001595061898838939;
            } else {
              result[0] += 0.0004347763859651299;
            }
          } else {
            result[0] += -0.0026936672280685374;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.005358500000000001283) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.7450000000000001066) ) ) {
            result[0] += -0.0007522728648384933;
          } else {
            result[0] += 0.0003241790323377691;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.7270847835843652351) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1627210000000000323) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
                result[0] += 0.004065547005810308;
              } else {
                result[0] += 0.0008929423433673315;
              }
            } else {
              result[0] += 0.006657313049156449;
            }
          } else {
            result[0] += -0.0006814854137083571;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8050000000000001599) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7050000000000000711) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004748500000000000117) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            result[0] += 0.0008322434750017812;
          } else {
            result[0] += 0.0024596218438784527;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
            result[0] += 0.002705208602630004;
          } else {
            result[0] += 0.006939983626198706;
          }
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
          result[0] += 0.00206718941734742;
        } else {
          result[0] += 0.004249758640700643;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9550000000000000711) ) ) {
        result[0] += 0.0044086791575207425;
      } else {
        result[0] += 0.005528314206451704;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5950000000000000844) ) ) {
    if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1750000000000000167) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.02500000000000000486) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0006695000000000000647) ) ) {
            result[0] += -0.00795733757412954;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5259885771356785922) ) ) {
              if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.05751864358971629093) ) ) {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
                  result[0] += -0.002231647104069012;
                } else {
                  result[0] += -0.008565999255996517;
                }
              } else {
                result[0] += 0.00025693760958185553;
              }
            } else {
              result[0] += -0.0074473899628363155;
            }
          }
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6968016071608041928) ) ) {
            result[0] += -0.006228584549567548;
          } else {
            result[0] += -0.006896742797407437;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004225500000000000957) ) ) {
          if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
            result[0] += -0.006343893080370226;
          } else {
            result[0] += -0.005029722552654623;
          }
        } else {
          if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.009795894273113748066) ) ) {
            result[0] += -0.0016436335662701335;
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
              result[0] += -0.0034509724350247407;
            } else {
              result[0] += -0.004873574592618752;
            }
          }
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3450000000000000289) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6050666370100503677) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02264200000000000587) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.3150000000000000577) ) ) {
                result[0] += -0.002398690937016302;
              } else {
                result[0] += 0.0006005795740484564;
              }
            } else {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4850000000000000422) ) ) {
                result[0] += -0.002451523370780005;
              } else {
                result[0] += -0.00036745704392102834;
              }
            }
          } else {
            result[0] += 0.00025123400137467037;
          }
        } else {
          if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1750000000000000167) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.07382500000000001561) ) ) {
              result[0] += -0.004274650298566687;
            } else {
              result[0] += -0.0004839559403034768;
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8490362337185931585) ) ) {
              result[0] += -0.002090702729120478;
            } else {
              result[0] += -0.004949095406924091;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004655500000000000783) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6550000000000001377) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
              result[0] += 0.0006587270152154302;
            } else {
              result[0] += -0.0011105187798210931;
            }
          } else {
            result[0] += 0.00030561902369455;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.3905483718502500978) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1627210000000000323) ) ) {
              result[0] += 0.0016080587974277184;
            } else {
              result[0] += 0.006536794424776392;
            }
          } else {
            result[0] += -7.19180960109329e-05;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8250000000000000666) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7450000000000001066) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002305500000000000691) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            result[0] += 0.0008596469132440066;
          } else {
            result[0] += 0.0022657384639081673;
          }
        } else {
          result[0] += 0.00315497639009296;
        }
      } else {
        result[0] += 0.0038665012989108124;
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
        result[0] += 0.004323869239267905;
      } else {
        result[0] += 0.005294893440783657;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5950000000000000844) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1050000000000000239) ) ) {
      if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0007095000000000001696) ) ) {
          result[0] += -0.007621356701865662;
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6644777202348807199) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4737195465326633492) ) ) {
                result[0] += -0.0053462787949072575;
              } else {
                result[0] += -0.0067410078361226965;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.05500000000000000722) ) ) {
                result[0] += -0.0034220289850396108;
              } else {
                result[0] += 0.0005682738889750003;
              }
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01243050000000000231) ) ) {
              result[0] += -0.007132940493715144;
            } else {
              result[0] += -0.007977395970497837;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7392963230402010977) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.06441400000000001291) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1250000000000000278) ) ) {
              result[0] += -0.005554539127550219;
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.468148307738693481) ) ) {
                result[0] += -0.0005734560448765392;
              } else {
                result[0] += -0.004026966249116156;
              }
            }
          } else {
            result[0] += -0.0014687943669769944;
          }
        } else {
          result[0] += -0.006314377493167728;
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3450000000000000289) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2150000000000000244) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004225500000000000957) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2050000000000000433) ) ) {
              result[0] += -0.004655724265448416;
            } else {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
                result[0] += -0.0023434277984026018;
              } else {
                result[0] += -0.0035201261799900287;
              }
            }
          } else {
            result[0] += -0.0021890742238807413;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007751500000000000577) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000210500000000000048) ) ) {
              result[0] += -0.0012309922424838338;
            } else {
              result[0] += -0.0019497498767742992;
            }
          } else {
            result[0] += -0.0007373461993691041;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004655500000000000783) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6550000000000001377) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2750000000000000777) ) ) {
                result[0] += -0.007049519927830502;
              } else {
                result[0] += 0.0010686908292383216;
              }
            } else {
              result[0] += -0.0010622843463393321;
            }
          } else {
            result[0] += 0.0002927149404877302;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.3905483718502500978) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1627210000000000323) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.3450000000000000289) ) ) {
                result[0] += -0.0018085232142918684;
              } else {
                result[0] += 0.001649147757373305;
              }
            } else {
              result[0] += 0.006260792825977027;
            }
          } else {
            result[0] += -6.888151444024953e-05;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8250000000000000666) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7450000000000001066) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.04503850000000000908) ) ) {
          result[0] += 0.0019671499924493294;
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9774026691300493619) ) ) {
            result[0] += 0.006166871991353198;
          } else {
            result[0] += -1.0081767954533265e-05;
          }
        }
      } else {
        result[0] += 0.0037032468853691585;
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
        result[0] += 0.004141303482187644;
      } else {
        result[0] += 0.0050713283475340605;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5950000000000000844) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1050000000000000239) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0006695000000000000647) ) ) {
            result[0] += -0.00729956187430274;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4737195465326633492) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4578754035427136104) ) ) {
                result[0] += -0.0055875422413498455;
              } else {
                result[0] += 0.005171498163187378;
              }
            } else {
              if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6461954822149375) ) ) {
                result[0] += -0.005810907856251849;
              } else {
                result[0] += -0.007253995692100619;
              }
            }
          }
        } else {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.115000000000000005) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6968016071608041928) ) ) {
              result[0] += -0.005945790122779046;
            } else {
              result[0] += -0.0067486546719905775;
            }
          } else {
            result[0] += -0.0019796971854242136;
          }
        }
      } else {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004225500000000000957) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1250000000000000278) ) ) {
              result[0] += -0.005340159735521651;
            } else {
              result[0] += -0.00387463535955212;
            }
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4821784723869347311) ) ) {
              result[0] += -0.0009068321982208826;
            } else {
              result[0] += -0.0033485273968377615;
            }
          }
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
            result[0] += -0.005382987884802478;
          } else {
            result[0] += -0.007330873538170773;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3350000000000000755) ) ) {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1850000000000000255) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004225500000000000957) ) ) {
            result[0] += -0.0038897342307309874;
          } else {
            result[0] += -0.002317927413419622;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1113440000000000124) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8254037945979900703) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.468148307738693481) ) ) {
                result[0] += -0.0003564799098515224;
              } else {
                result[0] += -0.001816229590497726;
              }
            } else {
              result[0] += -0.004540310769285249;
            }
          } else {
            result[0] += 0.001589347652537072;
          }
        }
      } else {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4350000000000000533) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.08494950000000001111) ) ) {
            result[0] += -0.0005198783416372357;
          } else {
            result[0] += 0.002377438405546404;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004655500000000000783) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.5950000000000000844) ) ) {
              result[0] += -0.0008880765715458125;
            } else {
              result[0] += 0.00046059586634354714;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.3905483718502500978) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1627210000000000323) ) ) {
                result[0] += 0.0019190462810150626;
              } else {
                result[0] += 0.0061156945421122835;
              }
            } else {
              result[0] += 0.0003104769669966505;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8650000000000001021) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7450000000000001066) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.04503850000000000908) ) ) {
          result[0] += 0.001884091461353985;
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9774026691300493619) ) ) {
            result[0] += 0.0059064895441473956;
          } else {
            result[0] += -9.656087736773539e-06;
          }
        }
      } else {
        result[0] += 0.003428785668395747;
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9750000000000000888) ) ) {
        result[0] += 0.0041731748921167554;
      } else {
        result[0] += 0.004857202792866056;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5950000000000000844) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0007095000000000001696) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -0.0069913541172703045;
          } else {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += -0.007263281682844141;
            } else {
              result[0] += -0.005724670902096267;
            }
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6461954822149375) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4737195465326633492) ) ) {
                result[0] += -0.005111760801717361;
              } else {
                result[0] += -0.006211031126749779;
              }
            } else {
              result[0] += -0.0029746570084654136;
            }
          } else {
            result[0] += -0.00691205661230665;
          }
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6413622072216433878) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1750000000000000167) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.06276700000000001722) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3083650974108879672) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                  result[0] += -0.004580122174760511;
                } else {
                  result[0] += 0.0011342659305665877;
                }
              } else {
                result[0] += -0.005417608690169123;
              }
            } else {
              result[0] += -0.0010128965396653156;
            }
          } else {
            result[0] += -0.001954399006313244;
          }
        } else {
          result[0] += -0.0058359286022375365;
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3350000000000000755) ) ) {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1650000000000000355) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004225500000000000957) ) ) {
            result[0] += -0.004179024367169407;
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7683067979899498301) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.02500000000000000486) ) ) {
                result[0] += 0.002624941251859587;
              } else {
                result[0] += -0.002327255604765837;
              }
            } else {
              result[0] += -0.004612514538419534;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1030960000000000071) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8254037945979900703) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.468148307738693481) ) ) {
                result[0] += -0.0004855091443139771;
              } else {
                result[0] += -0.001848382999896704;
              }
            } else {
              result[0] += -0.004281213337874807;
            }
          } else {
            result[0] += 0.001136189800823616;
          }
        }
      } else {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4350000000000000533) ) ) {
          result[0] += -0.00034226785052059796;
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004655500000000000783) ) ) {
            result[0] += 0.0002218759675628964;
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.3905483718502500978) ) ) {
                result[0] += 0.0018430716760267488;
              } else {
                result[0] += 0.00012930552033523225;
              }
            } else {
              result[0] += 0.005260993039238108;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8650000000000001021) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7450000000000001066) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.04503850000000000908) ) ) {
          result[0] += 0.0018045398919108772;
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9774026691300493619) ) ) {
            result[0] += 0.005657101166367382;
          } else {
            result[0] += -9.248380918981733e-06;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02678800000000000278) ) ) {
          result[0] += 0.0027634352264343854;
        } else {
          result[0] += 0.0052968018140745554;
        }
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9750000000000000888) ) ) {
        result[0] += 0.0039969718685173095;
      } else {
        result[0] += 0.004652118213268062;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6150000000000001021) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1050000000000000239) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.02500000000000000486) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += -0.00669615974694939;
            } else {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                result[0] += -0.007106905948982252;
              } else {
                result[0] += -0.005684672478172479;
              }
            }
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5450375474120604524) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.2103007793702001138) ) ) {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
                  result[0] += -0.00040117474978877763;
                } else {
                  result[0] += -0.005590632465788441;
                }
              } else {
                result[0] += 0.0029134459783598282;
              }
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01446850000000000046) ) ) {
                result[0] += -0.00597719700166143;
              } else {
                result[0] += -0.006629868354545158;
              }
            }
          }
        } else {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1350000000000000366) ) ) {
            result[0] += -0.005795070829628963;
          } else {
            result[0] += -0.00033747671588245696;
          }
        }
      } else {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7392963230402010977) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004225500000000000957) ) ) {
            result[0] += -0.004620122168949578;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4821784723869347311) ) ) {
              result[0] += -0.0007165989025604081;
            } else {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                result[0] += 0.0008442636715619722;
              } else {
                result[0] += -0.003228381671933265;
              }
            }
          }
        } else {
          result[0] += -0.005243293697839747;
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3850000000000000644) ) ) {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2150000000000000244) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.06783400000000001928) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
              result[0] += -0.0028599377305134513;
            } else {
              result[0] += -0.005561430253431845;
            }
          } else {
            result[0] += -0.00010069865637447428;
          }
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02859250000000000333) ) ) {
              result[0] += -0.0010067006846827895;
            } else {
              result[0] += 0.0005639560054554549;
            }
          } else {
            result[0] += -0.002158696241443535;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004655500000000000783) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.5950000000000000844) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
              result[0] += 0.0005106788725619745;
            } else {
              result[0] += -0.0013298282690871943;
            }
          } else {
            result[0] += 0.00032215103869562023;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1932010000000000394) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.2273413669989351737) ) ) {
              result[0] += 0.0019393764980513172;
            } else {
              result[0] += 0.00029684130666651775;
            }
          } else {
            result[0] += 0.005329178700376787;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8650000000000001021) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7650000000000001243) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003581500000000000482) ) ) {
          result[0] += 0.0013717605674727648;
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1359205000000000274) ) ) {
            result[0] += 0.0029085494970364644;
          } else {
            result[0] += 0.006313932839940408;
          }
        }
      } else {
        result[0] += 0.003167332920147444;
      }
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9750000000000000888) ) ) {
        result[0] += 0.003828208625499367;
      } else {
        result[0] += 0.004455692873685878;
      }
    }
  }
}

