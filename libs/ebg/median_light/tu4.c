
#include "header.h"

void predict_unit4(union Entry* data, double* result) {
  unsigned int tmp;
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9050000000000001377) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.001612703387996924;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002803500000000000436) ) ) {
              result[0] += -0.001522737630841949;
            } else {
              result[0] += -0.0011587118068328139;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                result[0] += -0.0017116275201350573;
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.006921500000000001436) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.051391296366422923) ) ) {
                    result[0] += -0.0019723254002849033;
                  } else {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.82990551552763836) ) ) {
                      result[0] += 0.002010938103276173;
                    } else {
                      result[0] += -0.001443391277503879;
                    }
                  }
                } else {
                  result[0] += -0.0016720349269603893;
                }
              }
            } else {
              result[0] += -0.001952601820725137;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.06441400000000001291) ) ) {
            result[0] += -0.0014109858775953057;
          } else {
            result[0] += 0.00015724216140817563;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.6650000000000001465) ) ) {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1450000000000000455) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
            result[0] += -0.0018808668937804562;
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.03500000000000001027) ) ) {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
                result[0] += -0.0004190316992535739;
              } else {
                result[0] += 0.0012948640352215875;
              }
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
                result[0] += 0.0001514164490083187;
              } else {
                result[0] += -0.0011564616364231855;
              }
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.07584250000000002101) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8274453021105528938) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8145641537437187107) ) ) {
                result[0] += -0.00044100012122420666;
              } else {
                result[0] += 0.002205888337347128;
              }
            } else {
              result[0] += -0.0019774726604384384;
            }
          } else {
            result[0] += 0.0008755366426247489;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7550000000000001155) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3477174365476807805) ) ) {
              result[0] += 0.0012957744421267202;
            } else {
              result[0] += 0.00021762817271042965;
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9650000000000000799) ) ) {
              result[0] += 0.0018448939129521035;
            } else {
              result[0] += 0.00046267129026407087;
            }
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9993516786272610419) ) ) {
            result[0] += 0.001782528232136683;
          } else {
            result[0] += 6.221677768271117e-06;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9750000000000000888) ) ) {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9850000000000000977) ) ) {
          result[0] += 0.0015275788599519937;
        } else {
          if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9450000000000000622) ) ) {
            result[0] += 0.0007963753860319394;
          } else {
            result[0] += 0.0009528181296127428;
          }
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01594650000000000234) ) ) {
          result[0] += 0.0009524992271852506;
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.08390973343508316418) ) ) {
            result[0] += 0.0011885261709688594;
          } else {
            result[0] += 0.0007841264359096631;
          }
        }
      }
    } else {
      result[0] += 0.0010731092543813032;
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9450000000000000622) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.0015446105760539305;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5673593061306533292) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.06355808660527756393) ) ) {
                result[0] += -0.001632939020257415;
              } else {
                result[0] += 0.0018503833578100294;
              }
            } else {
              result[0] += -0.0014773398175819549;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                result[0] += -0.0016393578568402029;
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.006921500000000001436) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.051391296366422923) ) ) {
                    result[0] += -0.001889048349110106;
                  } else {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.82990551552763836) ) ) {
                      result[0] += 0.001926030716639217;
                    } else {
                      result[0] += -0.0013824472926702491;
                    }
                  }
                } else {
                  result[0] += -0.0016014369728102197;
                }
              }
            } else {
              result[0] += -0.001870157553808004;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.06441400000000001291) ) ) {
            result[0] += -0.0013514101386637649;
          } else {
            result[0] += 0.00015060296104066364;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5550000000000001599) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2850000000000000866) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003726500000000000212) ) ) {
                if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1550000000000000266) ) ) {
                  result[0] += -0.0013197545888327673;
                } else {
                  result[0] += -0.0007996821857279147;
                }
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.394135022639764854) ) ) {
                  result[0] += -0.00047852232407942405;
                } else {
                  result[0] += 0.003204416424936325;
                }
              }
            } else {
              result[0] += -0.007396992649124397;
            }
          } else {
            result[0] += -0.0019271153471041844;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.7760221401809592745) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01531200000000000096) ) ) {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
                result[0] += 0.0006804180463390083;
              } else {
                if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4550000000000000711) ) ) {
                  result[0] += -0.0008468335152464514;
                } else {
                  result[0] += 8.48576551021607e-06;
                }
              }
            } else {
              result[0] += 0.0007661987578918119;
            }
          } else {
            result[0] += -0.0005830878307624077;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01421250000000000117) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
            result[0] += 0.00037441900955252974;
          } else {
            result[0] += 0.0005649745073334043;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1270434093492826821) ) ) {
            if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7550000000000001155) ) ) {
              result[0] += 0.001801719952082529;
            } else {
              result[0] += 0.0015557099683520268;
            }
          } else {
            result[0] += 0.0006408124104893153;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9750000000000000888) ) ) {
        result[0] += 0.0009287831834011458;
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01594650000000000234) ) ) {
          result[0] += 0.0009122820668349354;
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.08390973343508316418) ) ) {
            result[0] += 0.0011383432981284733;
          } else {
            result[0] += 0.0007510184420049424;
          }
        }
      }
    } else {
      result[0] += 0.001027799604016129;
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9450000000000000622) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.00147939283157394;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002803500000000000436) ) ) {
              result[0] += -0.0013960660364059276;
            } else {
              result[0] += -0.0010408405626881221;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
                result[0] += -0.00126385344751472;
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  result[0] += -0.0015701396192622824;
                } else {
                  result[0] += -1.3540688302427733e-05;
                }
              }
            } else {
              result[0] += -0.0017911943126050535;
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6968016071608041928) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05663800000000000778) ) ) {
              result[0] += -0.0011743344161048994;
            } else {
              result[0] += 0.001582778494411222;
            }
          } else {
            result[0] += -0.0013583733337957625;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5550000000000001599) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2150000000000000244) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01731250000000000497) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
                result[0] += -0.00022359776845591798;
              } else {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1701831610694422292) ) ) {
                    result[0] += -0.0005035532831348574;
                  } else {
                    result[0] += -0.0038314177401767954;
                  }
                } else {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.05539262878325219158) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5556488633165830304) ) ) {
                      result[0] += 0.0018511890343708896;
                    } else {
                      result[0] += -0.00183448238043413;
                    }
                  } else {
                    result[0] += -0.001090474001314639;
                  }
                }
              }
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                result[0] += -5.804325160449874e-05;
              } else {
                result[0] += -0.007364070173056826;
              }
            }
          } else {
            result[0] += -0.001956770711789676;
          }
        } else {
          result[0] += -5.0201682436755255e-05;
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01421250000000000117) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7850000000000001421) ) ) {
            result[0] += 0.0003064139964977603;
          } else {
            result[0] += 0.0005252665942842259;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6754021834779359024) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.154253000000000029) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2070606536698188782) ) ) {
                result[0] += 0.0017966815306135098;
              } else {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6722423356281408413) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.4655737892380691911) ) ) {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5180644051256282356) ) ) {
                      result[0] += 0.0003724891451034313;
                    } else {
                      result[0] += 0.0013432007087726245;
                    }
                  } else {
                    result[0] += -0.0013340019256399788;
                  }
                } else {
                  result[0] += 0.001968878178299863;
                }
              }
            } else {
              result[0] += 0.0016064069122058043;
            }
          } else {
            result[0] += 0.00020656566316872222;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007451500000000000658) ) ) {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9550000000000000711) ) ) {
          result[0] += 0.0005315521121709538;
        } else {
          result[0] += 0.0008737629865884981;
        }
      } else {
        result[0] += 0.0009456816177900189;
      }
    } else {
      result[0] += 0.0009844030528138163;
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9450000000000000622) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.0014169287612309758;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5750608109547740154) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.08693186820944626136) ) ) {
                result[0] += -0.0015050460219336922;
              } else {
                result[0] += 0.0015643072506057911;
              }
            } else {
              if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.4655737892380691911) ) ) {
                result[0] += -0.0016864586239193607;
              } else {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6828811456281408399) ) ) {
                  result[0] += -0.00028212682727615475;
                } else {
                  result[0] += -0.0013371202545687222;
                }
              }
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
                result[0] += -0.0012104900480417304;
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  result[0] += -0.0015038439677404827;
                } else {
                  result[0] += -1.2968962869829026e-05;
                }
              }
            } else {
              result[0] += -0.0017155651185515417;
            }
          }
        } else {
          result[0] += -0.0011764673032199906;
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5550000000000001599) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2850000000000000866) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1550000000000000266) ) ) {
                  result[0] += -0.0016547506047228594;
                } else {
                  result[0] += -0.000627842200522266;
                }
              } else {
                if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.02500000000000000486) ) ) {
                  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.0650000000000000161) ) ) {
                    result[0] += -4.6451957150238394e-05;
                  } else {
                    result[0] += 0.0026497985139985357;
                  }
                } else {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.4612588522637047217) ) ) {
                    result[0] += 0.001152635020563055;
                  } else {
                    result[0] += -0.0007574990585616011;
                  }
                }
              }
            } else {
              result[0] += -0.006773739618027391;
            }
          } else {
            result[0] += -0.0017631269007571144;
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5694467910050252657) ) ) {
            result[0] += 0.0002488429556764378;
          } else {
            result[0] += -0.0003061317318615805;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01421250000000000117) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7850000000000001421) ) ) {
            result[0] += 0.0002934763473333102;
          } else {
            result[0] += 0.00050308838117279;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6754021834779359024) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.154253000000000029) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2070606536698188782) ) ) {
                result[0] += 0.0017208206509898422;
              } else {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6722423356281408413) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.4655737892380691911) ) ) {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5180644051256282356) ) ) {
                      result[0] += 0.0003567616198206577;
                    } else {
                      result[0] += 0.0012864870477579053;
                    }
                  } else {
                    result[0] += -0.0012776766627737464;
                  }
                } else {
                  result[0] += 0.0018857466784025683;
                }
              }
            } else {
              result[0] += 0.0015385799549420649;
            }
          } else {
            result[0] += 0.00019784388769487337;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
        result[0] += 0.0008368702887921499;
      } else {
        result[0] += 0.0010503499834617202;
      }
    } else {
      result[0] += 0.0009428388244192735;
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9450000000000000622) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.001357102097262125;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5673593061306533292) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.06355808660527756393) ) ) {
                result[0] += -0.0014414988027117055;
              } else {
                result[0] += 0.0018314082118431852;
              }
            } else {
              result[0] += -0.0013026259534679812;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
                result[0] += -0.0011593797993663382;
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  result[0] += -0.0014403475025819728;
                } else {
                  result[0] += -1.2421377271408668e-05;
                }
              }
            } else {
              result[0] += -0.001643129198925563;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.06441400000000001291) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2350000000000000144) ) ) {
              result[0] += -0.0011919831721423774;
            } else {
              result[0] += 0.006391792618446377;
            }
          } else {
            result[0] += 0.0002512720914622343;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5550000000000001599) ) ) {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.1650000000000000355) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01731250000000000497) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8274453021105528938) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8145641537437187107) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
                    if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                      result[0] += 0.0008778227669864619;
                    } else {
                      result[0] += -0.0009937161241284184;
                    }
                  } else {
                    result[0] += -0.002615620116531868;
                  }
                } else {
                  result[0] += 0.001566033557322192;
                }
              } else {
                result[0] += -0.002023097377599413;
              }
            } else {
              result[0] += -0.00011763629249740651;
            }
          } else {
            result[0] += -0.0026152717104105895;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03034700000000000245) ) ) {
            result[0] += -0.0001998838756056199;
          } else {
            result[0] += 0.00047847674610027854;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03105600000000000374) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7750000000000001332) ) ) {
            result[0] += 0.0003283977620987708;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.03588532983514210878) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9750000000000000888) ) ) {
                result[0] += 0.001752730490585199;
              } else {
                result[0] += 0.0005188736815858353;
              }
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
                result[0] += -0.0005050594992493093;
              } else {
                result[0] += 0.0003952029095403778;
              }
            }
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9993516786272610419) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1811070000000000457) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1890520899528410625) ) ) {
                result[0] += 0.0016478422489106523;
              } else {
                result[0] += 0.0010086790359028943;
              }
            } else {
              result[0] += 0.0014897049658671546;
            }
          } else {
            result[0] += -0.000850241539999607;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
        result[0] += 0.0008004071412144758;
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007171500000000001658) ) ) {
          result[0] += 0.000801535303065987;
        } else {
          result[0] += 0.0010060012926668047;
        }
      }
    } else {
      result[0] += 0.0009030295530792572;
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9450000000000000622) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.0012998014810520423;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002803500000000000436) ) ) {
              result[0] += -0.001225662844942808;
            } else {
              result[0] += -0.0009664644670598294;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
                result[0] += -0.0011104275672098643;
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8274453021105528938) ) ) {
                    result[0] += -0.0013795320343713603;
                  } else {
                    result[0] += -0.0013795320343713603;
                  }
                } else {
                  result[0] += -1.1896912256384771e-05;
                }
              }
            } else {
              result[0] += -0.0015737517248201431;
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6968016071608041928) ) ) {
            result[0] += -0.0009097351384197478;
          } else {
            result[0] += -0.0012051858435174066;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5550000000000001599) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.29500000000000004) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1550000000000000266) ) ) {
                result[0] += -0.0015808522400004533;
              } else {
                result[0] += -0.0006870345287117017;
              }
            } else {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.03500000000000001027) ) ) {
                result[0] += 0.00020927620593637024;
              } else {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
                  result[0] += 7.392128204277009e-05;
                } else {
                  if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.05500000000000000722) ) ) {
                    result[0] += -0.0014236371443819313;
                  } else {
                    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1185261981962025396) ) ) {
                      result[0] += -0.0025968870529538154;
                    } else {
                      result[0] += -0.0005142351546771433;
                    }
                  }
                }
              }
            }
          } else {
            result[0] += -0.0024795924838042194;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.7760221401809592745) ) ) {
            result[0] += 7.626360616699336e-05;
          } else {
            result[0] += -0.0005323879847978719;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03105600000000000374) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7750000000000001332) ) ) {
            result[0] += 0.0003145318973504686;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.03588532983514210878) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9750000000000000888) ) ) {
                result[0] += 0.00167872534582612;
              } else {
                result[0] += 0.0004969653949874675;
              }
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
                result[0] += -0.00048373448576054907;
              } else {
                result[0] += 0.0003785163460973106;
              }
            }
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9993516786272610419) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1811070000000000457) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1890520899528410625) ) ) {
                result[0] += 0.0015782657767571704;
              } else {
                result[0] += 0.0009660898081417486;
              }
            } else {
              result[0] += 0.0014268054886003951;
            }
          } else {
            result[0] += -0.0008143419829451499;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
        result[0] += 0.0007666117307563642;
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007171500000000001658) ) ) {
          result[0] += 0.0007676922584840966;
        } else {
          result[0] += 0.0009635251266552406;
        }
      }
    } else {
      result[0] += 0.0008649011396372984;
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.0012449202558551188;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5750608109547740154) ) ) {
              if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.05539262878325219158) ) ) {
                result[0] += -0.0017124543462605137;
              } else {
                result[0] += 0.0005405105354016417;
              }
            } else {
              if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.4655737892380691911) ) ) {
                result[0] += -0.0015085002927395599;
              } else {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6828811456281408399) ) ) {
                  result[0] += -0.00017008213496838497;
                } else {
                  result[0] += -0.001173911958681035;
                }
              }
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
                result[0] += -0.0010635422341268527;
              } else {
                result[0] += -0.0013212843639783202;
              }
            } else {
              result[0] += -0.0015073035601788822;
            }
          }
        } else {
          result[0] += -0.0010375295434224081;
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6650000000000001465) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.25500000000000006) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.468148307738693481) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4558178340201005097) ) ) {
              result[0] += -6.822203129205e-05;
            } else {
              result[0] += 0.002844323804261582;
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.04871150000000001173) ) ) {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                    if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1701831610694422292) ) ) {
                      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2545696998002126565) ) ) {
                        result[0] += -0.002229713250764349;
                      } else {
                        result[0] += 0.0003155135413791806;
                      }
                    } else {
                      result[0] += -0.003213776812073183;
                    }
                  } else {
                    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.009795894273113748066) ) ) {
                      result[0] += 0.000544964428205657;
                    } else {
                      result[0] += -0.0008458375482427654;
                    }
                  }
                } else {
                  result[0] += 0.00016067876057858146;
                }
              } else {
                result[0] += -0.0062726142322757725;
              }
            } else {
              result[0] += -0.001644413724318773;
            }
          }
        } else {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.00196950000000000033) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
              result[0] += 0.0004250255517924608;
            } else {
              result[0] += -0.00045701239191357003;
            }
          } else {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3477174365476807805) ) ) {
              result[0] += 0.001580585166884407;
            } else {
              result[0] += 0.00014028909720752725;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02741500000000000534) ) ) {
          if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2252565153835193457) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
              result[0] += 0.000992629982459695;
            } else {
              result[0] += 0.0008042534451878345;
            }
          } else {
            result[0] += 0.00034743396266184815;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1324529432504036319) ) ) {
            result[0] += 0.0012264807903489474;
          } else {
            result[0] += 0.0007481392076240808;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007171500000000001658) ) ) {
        result[0] += 0.0007352781611515584;
      } else {
        result[0] += 0.0009228424222348249;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
        result[0] += 0.000828382613608929;
      } else {
        result[0] += 0.000828382613608929;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.0011923562682694937;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.932576353658176371) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6852090990703517681) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.482877277201360311) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5750608109547740154) ) ) {
                  if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.05539262878325219158) ) ) {
                    result[0] += -0.0016401497720723796;
                  } else {
                    result[0] += 0.0003984274757631628;
                  }
                } else {
                  result[0] += -0.001339269683728476;
                }
              } else {
                result[0] += 0.0005087185339566204;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                result[0] += -0.0012654960718539133;
              } else {
                result[0] += -0.0005256001973686831;
              }
            }
          } else {
            result[0] += -0.0012654960718539133;
          }
        } else {
          result[0] += -0.0009937221671798922;
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6650000000000001465) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2650000000000000688) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.468148307738693481) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4558178340201005097) ) ) {
                result[0] += -6.897643013258829e-05;
              } else {
                result[0] += 0.0027007806577850624;
              }
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.04871150000000001173) ) ) {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                    if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1547679134652330257) ) ) {
                      result[0] += -0.0006670705561783217;
                    } else {
                      result[0] += -0.003084013328416017;
                    }
                  } else {
                    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.009795894273113748066) ) ) {
                      result[0] += 0.000532885512588926;
                    } else {
                      result[0] += -0.0007985825079745079;
                    }
                  }
                } else {
                  result[0] += 0.0001405356756068692;
                }
              } else {
                result[0] += -0.00600776705424646;
              }
            }
          } else {
            result[0] += -0.0015499120878300664;
          }
        } else {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.00196950000000000033) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
              result[0] += 0.0004686780480442723;
            } else {
              result[0] += -0.0004434260291335358;
            }
          } else {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3477174365476807805) ) ) {
              result[0] += 0.0014888129320625857;
            } else {
              result[0] += 0.0001546978238620183;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
            if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.03945373639888280493) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01030150000000000163) ) ) {
                result[0] += 0.0004892747304947091;
              } else {
                result[0] += 0.0014746260935445386;
              }
            } else {
              result[0] += 0.00023483999530060987;
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9850000000000000977) ) ) {
              result[0] += 0.0011776755831512699;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.111039020874343905) ) ) {
                result[0] += 0.0007119532472344695;
              } else {
                result[0] += 0.0003082526703236372;
              }
            }
          }
        } else {
          result[0] += 0.0011746953681625073;
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007171500000000001658) ) ) {
        result[0] += 0.000704232676950479;
      } else {
        result[0] += 0.0008838774544807093;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
        result[0] += 0.0007934060010804585;
      } else {
        result[0] += 0.0007934060010804585;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.001142011678093387;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.932576353658176371) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6852090990703517681) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.482877277201360311) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5750608109547740154) ) ) {
                  if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.05539262878325219158) ) ) {
                    result[0] += -0.0015708980976359638;
                  } else {
                    result[0] += 0.0003816047621867007;
                  }
                } else {
                  result[0] += -0.0012827220014988603;
                }
              } else {
                result[0] += 0.0004872390258694895;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                result[0] += -0.001212063316223397;
              } else {
                result[0] += -0.0005034078986093443;
              }
            }
          } else {
            result[0] += -0.001212063316223397;
          }
        } else {
          result[0] += -0.0009517644599182931;
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6650000000000001465) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.25500000000000006) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.468148307738693481) ) ) {
              result[0] += 0.00018542348125161103;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.04871150000000001173) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.394135022639764854) ) ) {
                    if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                      result[0] += 0.0009082071588054397;
                    } else {
                      result[0] += -0.0008468906673909533;
                    }
                  } else {
                    result[0] += 0.0012184006573917002;
                  }
                } else {
                  result[0] += 0.00014796065127817032;
                }
              } else {
                result[0] += -0.005754102458966962;
              }
            }
          } else {
            result[0] += -0.0015095404249692492;
          }
        } else {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.00196950000000000033) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
              result[0] += 0.0003872909059738977;
            } else {
              result[0] += -0.0004231730653486068;
            }
          } else {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3477174365476807805) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4005449041457286863) ) ) {
                result[0] += 0.00037677741671142704;
              } else {
                result[0] += 0.002384433362960646;
              }
            } else {
              result[0] += 0.00012783393087531029;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.03945373639888280493) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01421250000000000117) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.2635054734422110356) ) ) {
                result[0] += 0.0015123797651637554;
              } else {
                result[0] += 0.0005546068827838347;
              }
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5131783528140704265) ) ) {
                if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1916738466035730337) ) ) {
                  result[0] += 0.0012682621954075472;
                } else {
                  result[0] += 0.00030780933561420416;
                }
              } else {
                result[0] += 0.0013718978212758338;
              }
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6722423356281408413) ) ) {
              result[0] += 0.0001706771158033136;
            } else {
              result[0] += 0.00045354191160203584;
            }
          }
        } else {
          result[0] += 0.001125096470194081;
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007171500000000001658) ) ) {
        result[0] += 0.0006744980192368474;
      } else {
        result[0] += 0.0008465576957844988;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
        result[0] += 0.0007599061981854469;
      } else {
        result[0] += 0.0007599061981854469;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9550000000000000711) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.001093792776209823;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4389499174623116007) ) ) {
                result[0] += 0.002816714698929093;
              } else {
                result[0] += -0.001212523309182592;
              }
            } else {
              result[0] += -0.0001954993102923735;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.932576353658176371) ) ) {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6852090990703517681) ) ) {
                  result[0] += 0.004192946479709185;
                } else {
                  result[0] += -0.0011608866397998972;
                }
              } else {
                result[0] += -0.00034668601903127674;
              }
            } else {
              result[0] += -0.0011608866397998972;
            }
          }
        } else {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2350000000000000144) ) ) {
            result[0] += -0.0009156820792025808;
          } else {
            result[0] += 0.006286276160061974;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5750000000000000666) ) ) {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.29500000000000004) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1550000000000000266) ) ) {
                result[0] += -0.0014089142203087901;
              } else {
                result[0] += -0.0006036543500925165;
              }
            } else {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.03500000000000001027) ) ) {
                if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.04500000000000000527) ) ) {
                  result[0] += -0.00019142091413962932;
                } else {
                  result[0] += 0.0014752020476253049;
                }
              } else {
                result[0] += -0.0005563795101381642;
              }
            }
          } else {
            result[0] += -0.002154099460166889;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.7760221401809592745) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01531200000000000096) ) ) {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
                result[0] += 0.0007699449935412824;
              } else {
                if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4550000000000000711) ) ) {
                  result[0] += -0.0007489545861453457;
                } else {
                  result[0] += 2.281083004353145e-05;
                }
              }
            } else {
              result[0] += 0.0007069804828869526;
            }
          } else {
            result[0] += -0.0004716817761176137;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02361250000000000501) ) ) {
          if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.212199032544347022) ) ) {
            result[0] += 0.0023014491084924742;
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
              result[0] += 7.09571074149118e-05;
            } else {
              result[0] += 0.0004132233216766267;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.08693186820944626136) ) ) {
              result[0] += 0.0011300195566520017;
            } else {
              result[0] += 0.0003558901047576165;
            }
          } else {
            result[0] += 0.001106563982114762;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.008191000000000002099) ) ) {
        result[0] += 0.0006460188412791084;
      } else {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9750000000000000888) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            result[0] += 0.0011698121618746351;
          } else {
            result[0] += 0.0005830545135150922;
          }
        } else {
          result[0] += 0.0005941918745015907;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
        result[0] += 0.0007278208499233429;
      } else {
        result[0] += 0.0007278208499233429;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9550000000000000711) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.001047609810160767;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5694467910050252657) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.06355808660527756393) ) ) {
                result[0] += -0.0011165153694603074;
              } else {
                result[0] += 0.001666130040263362;
              }
            } else {
              result[0] += -0.0010509347324154047;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.932576353658176371) ) ) {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6852090990703517681) ) ) {
                  result[0] += 0.004015908644819725;
                } else {
                  result[0] += -0.0011118707846591634;
                }
              } else {
                result[0] += -0.0003320479733293435;
              }
            } else {
              result[0] += -0.0011118707846591634;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.06441400000000001291) ) ) {
            result[0] += -0.0009214928618032116;
          } else {
            result[0] += 0.0004561628351220567;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4950000000000000511) ) ) {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2350000000000000144) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0006325000000000001411) ) ) {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1550000000000000266) ) ) {
                result[0] += -0.0012779453937504849;
              } else {
                result[0] += -0.0005718983966006724;
              }
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4306236034422111225) ) ) {
                result[0] += 0.0009261722403539763;
              } else {
                result[0] += -0.00046206479900274226;
              }
            }
          } else {
            result[0] += -0.0020917019723016976;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
            result[0] += -0.00016654495789500685;
          } else {
            result[0] += 0.0021933169553234825;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01421250000000000117) ) ) {
          if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.212199032544347022) ) ) {
            result[0] += 0.0017603666525537345;
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8650000000000001021) ) ) {
              result[0] += 0.0001966566319160417;
            } else {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2834761482106662456) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4129968667336683663) ) ) {
                  result[0] += 0.0003090802957045253;
                } else {
                  result[0] += 0.0007721525855924503;
                }
              } else {
                result[0] += 0.0002576099101459704;
              }
            }
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1324529432504036319) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
              result[0] += 0.001247330382440935;
            } else {
              result[0] += 0.0010079986474179857;
            }
          } else {
            result[0] += 0.00035751187114969684;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.008191000000000002099) ) ) {
        result[0] += 0.000618742133238278;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.06355808660527756393) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            result[0] += 0.0009400743707623033;
          } else {
            if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9750000000000000888) ) ) {
              result[0] += 0.0006495985173046517;
            } else {
              result[0] += 0.000785725251159769;
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6152470170603016042) ) ) {
            result[0] += 0.00039171505551331595;
          } else {
            result[0] += 0.0005460641751158502;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
        result[0] += 0.0006970902340947423;
      } else {
        result[0] += 0.0006970902340947423;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9550000000000000711) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.0010033768170860055;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                result[0] += -0.0009241672272597848;
              } else {
                result[0] += -9.927115583088397e-05;
              }
            } else {
              result[0] += -0.0010649245149308274;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8274453021105528938) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.280667053512810405) ) ) {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                    result[0] += -0.0008180649729801404;
                  } else {
                    result[0] += 0.006457763469005054;
                  }
                } else {
                  result[0] += -0.0010649245149308274;
                }
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  result[0] += -0.0010649245149308274;
                } else {
                  result[0] += 0.0002449652574379211;
                }
              }
            } else {
              result[0] += -0.0012430894645049193;
            }
          }
        } else {
          result[0] += -0.0008358913987643197;
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4950000000000000511) ) ) {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.2350000000000000144) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1550000000000000266) ) ) {
                result[0] += -0.0012954675519511302;
              } else {
                result[0] += -0.0005448558352597228;
              }
            } else {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.03500000000000001027) ) ) {
                result[0] += 0.00027165607894482415;
              } else {
                result[0] += -0.0005381277854869721;
              }
            }
          } else {
            result[0] += -0.0020033845110122824;
          }
        } else {
          result[0] += -0.00012646850315649056;
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02361250000000000501) ) ) {
          if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2252565153835193457) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8350000000000000755) ) ) {
              result[0] += 0.0006204964807570762;
            } else {
              result[0] += 0.0006842537868655794;
            }
          } else {
            result[0] += 0.0001897238405802768;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9284011333411857914) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.2059025000000000161) ) ) {
                if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9650000000000000799) ) ) {
                  result[0] += 0.0013468849995155138;
                } else {
                  result[0] += 0.00013836028065980038;
                }
              } else {
                result[0] += 0.0012591393275838709;
              }
            } else {
              result[0] += -0.0007669054813704931;
            }
          } else {
            result[0] += 0.0009351372469704907;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.008191000000000002099) ) ) {
        result[0] += 0.0005926171234978735;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.06355808660527756393) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            result[0] += 0.0009003818223264437;
          } else {
            if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9750000000000000888) ) ) {
              result[0] += 0.0006221706654092015;
            } else {
              result[0] += 0.0007525497508388247;
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6152470170603016042) ) ) {
            result[0] += 0.0003751757589453128;
          } else {
            result[0] += 0.0005230078304329318;
          }
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
        result[0] += 0.0006676571501372117;
      } else {
        result[0] += 0.0006676571501372117;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9750000000000000888) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.000961011463715813;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                  result[0] += -0.0009072586839936899;
                } else {
                  result[0] += -0.0007859216205137559;
                }
              } else {
                result[0] += -9.507965217579949e-05;
              }
            } else {
              result[0] += -0.0010199604469761279;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8274453021105528938) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.280667053512810405) ) ) {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0003425000000000000852) ) ) {
                    result[0] += -0.0007835239998682312;
                  } else {
                    result[0] += 0.00639621276361684;
                  }
                } else {
                  result[0] += -0.0010199604469761279;
                }
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  result[0] += -0.0010199604469761279;
                } else {
                  result[0] += 0.00023462214454348791;
                }
              }
            } else {
              result[0] += -0.0011906027780101483;
            }
          }
        } else {
          result[0] += -0.0008005977444913408;
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7050000000000000711) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4550000000000000711) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4292508528894472541) ) ) {
              result[0] += 0.0002704012499939694;
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.04503850000000000908) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8274453021105528938) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8145641537437187107) ) ) {
                    result[0] += -0.0006466052093621418;
                  } else {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003120500000000000444) ) ) {
                      result[0] += 0.0016360186334335176;
                    } else {
                      result[0] += 0.007309603569702827;
                    }
                  }
                } else {
                  result[0] += -0.0013157301571294403;
                }
              } else {
                result[0] += 0.0001323008279568572;
              }
            }
          } else {
            result[0] += -0.0019645485373449923;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.7760221401809592745) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01531200000000000096) ) ) {
              result[0] += 0.00010377589149275209;
            } else {
              result[0] += 0.0009819532152591562;
            }
          } else {
            result[0] += -0.00041167387366860273;
          }
        }
      } else {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.04742850000000000538) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9850000000000000977) ) ) {
              result[0] += 0.0009495890042724877;
            } else {
              result[0] += 0.00011952398825018233;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
              result[0] += 0.0006378769964817126;
            } else {
              result[0] += 0.0002768056210162796;
            }
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
            result[0] += 0.0009511791351039391;
          } else {
            result[0] += 0.0008998750500027744;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.07127303416489440269) ) ) {
        result[0] += 0.0007207750121962391;
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01594650000000000234) ) ) {
          result[0] += 0.0005009249885988766;
        } else {
          result[0] += 0.00036961513868717996;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
        result[0] += 0.0006394668126547858;
      } else {
        result[0] += 0.0006394668126547858;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9750000000000000888) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.0009204348931195675;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.803731059838205808) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5694467910050252657) ) ) {
              if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.05539262878325219158) ) ) {
                result[0] += -0.001347176648617656;
              } else {
                result[0] += 0.0006278950001422493;
              }
            } else {
              result[0] += -0.0008859645776487601;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.932576353658176371) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
                  result[0] += -0.0007407370891977411;
                } else {
                  result[0] += 0.0005470934891004856;
                }
              } else {
                if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                  result[0] += -0.000976894886736002;
                } else {
                  result[0] += -0.0004768579002902056;
                }
              }
            } else {
              result[0] += -0.000976894886736002;
            }
          }
        } else {
          result[0] += -0.0007667942862339954;
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7050000000000000711) ) ) {
        if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.25500000000000006) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.468148307738693481) ) ) {
            result[0] += 0.00020607406141142544;
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.394135022639764854) ) ) {
                  if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                    result[0] += 0.0010373964067177156;
                  } else {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02972700000000000342) ) ) {
                      result[0] += -0.0007417879372715114;
                    } else {
                      result[0] += -1.6012543768484364e-05;
                    }
                  }
                } else {
                  result[0] += 0.0012591958732589004;
                }
              } else {
                result[0] += -0.0051643416256539985;
              }
            } else {
              result[0] += -0.001272645915977895;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.005358500000000001283) ) ) {
            if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
              result[0] += -0.00015487733072367768;
            } else {
              result[0] += 0.0007441343748534501;
            }
          } else {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
                result[0] += 0.0005748554953245415;
              } else {
                result[0] += 0.003884646049831059;
              }
            } else {
              result[0] += 0.00022127925631181217;
            }
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9850000000000000977) ) ) {
            if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.0176232216271788554) ) ) {
              result[0] += 0.0012425059838563617;
            } else {
              result[0] += 0.0005240257483781431;
            }
          } else {
            result[0] += 0.00014084985416706699;
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            result[0] += 0.0009439085124723064;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.08693186820944626136) ) ) {
              result[0] += 0.0005437239229056187;
            } else {
              result[0] += 0.0002434272682096801;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.07127303416489440269) ) ) {
        result[0] += 0.0006903418911871441;
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01594650000000000234) ) ) {
          result[0] += 0.00047977454562214564;
        } else {
          result[0] += 0.0003540089619300463;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
        result[0] += 0.000612466749442931;
      } else {
        result[0] += 0.000612466749442931;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9750000000000000888) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.0008815715779250691;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.803731059838205808) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5694467910050252657) ) ) {
              if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.05539262878325219158) ) ) {
                result[0] += -0.001290295112390308;
              } else {
                result[0] += 0.0006013835309639422;
              }
            } else {
              if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.178455187992527714) ) ) {
                result[0] += -0.0014244458018429526;
              } else {
                result[0] += -0.0008094314606497061;
              }
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.932576353658176371) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01196600000000000268) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.051391296366422923) ) ) {
                    result[0] += -0.0011316888522985595;
                  } else {
                    result[0] += -0.00027854598084847893;
                  }
                } else {
                  result[0] += 0.002645181741629534;
                }
              } else {
                if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                  result[0] += -0.0009356476739467935;
                } else {
                  result[0] += -0.0004567236365628118;
                }
              }
            } else {
              result[0] += -0.0009356476739467935;
            }
          }
        } else {
          result[0] += -0.0007344181037815327;
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7050000000000000711) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4550000000000000711) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4292508528894472541) ) ) {
              result[0] += 0.00025028314023089354;
            } else {
              result[0] += -0.0005442471214515542;
            }
          } else {
            result[0] += -0.001827865205013928;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.7760221401809592745) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1720305000000000306) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
                if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3763018001168558224) ) ) {
                  result[0] += 0.0008063387745204428;
                } else {
                  result[0] += 0.005532857907804159;
                }
              } else {
                result[0] += 0.00012889412948452223;
              }
            } else {
              result[0] += 0.001803593748321166;
            }
          } else {
            result[0] += -0.00039552502521350314;
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9650000000000000799) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004848500000000001246) ) ) {
              result[0] += 0.0002550341790367068;
            } else {
              result[0] += 0.0012245288782394025;
            }
          } else {
            result[0] += 0.00020260394729924681;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
              result[0] += 0.0009285683482642837;
            } else {
              result[0] += 0.0005184936344777299;
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1202115000000000128) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9850000000000000977) ) ) {
                result[0] += 0.0009589773358137934;
              } else {
                result[0] += 0.0001992974499654047;
              }
            } else {
              result[0] += 0.0009348332708306855;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01291500000000000113) ) ) {
        result[0] += 0.0005080139129560587;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.07127303416489440269) ) ) {
          result[0] += 0.0006611937409923584;
        } else {
          result[0] += 0.00033906172125935;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
        result[0] += 0.0005866067038191952;
      } else {
        result[0] += 0.0005866067038191952;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9750000000000000888) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -0.0008443491797353443;
      } else {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.803731059838205808) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5694467910050252657) ) ) {
              result[0] += -0.000431495384475606;
            } else {
              result[0] += -0.000814380252555885;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.932576353658176371) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
                  result[0] += -0.0006977001296911697;
                } else {
                  result[0] += 0.0004223560580901285;
                }
              } else {
                if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                  result[0] += -0.0008961420329336059;
                } else {
                  result[0] += -0.00043743949731819896;
                }
              }
            } else {
              result[0] += -0.0008961420329336059;
            }
          }
        } else {
          result[0] += -0.0007034089335890902;
        }
      }
    } else {
      if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7050000000000000711) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3450000000000000289) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7240686518592965859) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                  result[0] += 0.0013721606045300127;
                } else {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.468148307738693481) ) ) {
                    result[0] += 0.00021638605059672725;
                  } else {
                    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                      if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.121863051132545086) ) ) {
                        result[0] += -0.0006688130101856023;
                      } else {
                        result[0] += -0.0029383976076920305;
                      }
                    } else {
                      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.009795894273113748066) ) ) {
                        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5673593061306533292) ) ) {
                          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5458973873869347182) ) ) {
                            result[0] += 0.00022713183549296902;
                          } else {
                            result[0] += 0.0031226120713360155;
                          }
                        } else {
                          result[0] += -0.0017177347393025615;
                        }
                      } else {
                        result[0] += -0.0005205894006162325;
                      }
                    }
                  }
                }
              } else {
                result[0] += -0.005022283703478878;
              }
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9186477097784532253) ) ) {
                result[0] += 0.0007028582510474143;
              } else {
                result[0] += 0.00909098288153197;
              }
            }
          } else {
            result[0] += -0.000799860522592148;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.04503850000000000908) ) ) {
            result[0] += 6.697283565371987e-05;
          } else {
            result[0] += 0.000985682576625927;
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9650000000000000799) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004848500000000001246) ) ) {
              result[0] += 0.00024426592833330093;
            } else {
              result[0] += 0.0011728258711983575;
            }
          } else {
            result[0] += 0.00019404944646230846;
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            result[0] += 0.0008648473436952595;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.08693186820944626136) ) ) {
              result[0] += 0.0004988741502097935;
            } else {
              result[0] += 0.00022473420214335648;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.005358500000000001283) ) ) {
        result[0] += 0.0004865641559227412;
      } else {
        result[0] += 0.0004865641559227412;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
        result[0] += 0.000561838541077707;
      } else {
        result[0] += 0.000561838541077707;
      }
    }
  }
}

