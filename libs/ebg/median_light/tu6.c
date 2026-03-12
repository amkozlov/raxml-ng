
#include "header.h"

void predict_unit6(union Entry* data, double* result) {
  unsigned int tmp;
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.0004055259823052824;
    } else {
      if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.560956224143777993) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += -0.0004214481697830089;
            } else {
              result[0] += 0.0007329429934472062;
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += -0.0004304011739602343;
            } else {
              result[0] += -7.547495429645447e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.009542500000000000634) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9189305784170854752) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                result[0] += -0.0004304011739602343;
              } else {
                result[0] += -3.449478173300974e-05;
              }
            } else {
              result[0] += -0.0004304011739602343;
            }
          } else {
            result[0] += -0.0005159706491518265;
          }
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.29500000000000004) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.06441400000000001291) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
                result[0] += -0.00035420979012977435;
              } else {
                result[0] += -0.0008920376524127842;
              }
            } else {
              result[0] += 0.000414013186029173;
            }
          } else {
            if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09250981134579591703) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01314200000000000264) ) ) {
                  if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
                    result[0] += 0.0013563729047800703;
                  } else {
                    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.001886500000000000373) ) ) {
                      if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.05751864358971629093) ) ) {
                        result[0] += -0.00014019880910699412;
                      } else {
                        result[0] += -0.0010713888634601167;
                      }
                    } else {
                      result[0] += 0.000156846181542298;
                    }
                  }
                } else {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5131783528140704265) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
                      result[0] += 0.0007087646118486343;
                    } else {
                      result[0] += -0.0009136480418704586;
                    }
                  } else {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.2059025000000000161) ) ) {
                      result[0] += 0.0010767947834967886;
                    } else {
                      result[0] += 0.0014313307253973327;
                    }
                  }
                }
              } else {
                result[0] += 0.0031088042563960842;
              }
            } else {
              result[0] += -3.450662744368918e-05;
            }
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
              result[0] += 0.000544338944847041;
            } else {
              result[0] += 0.00043180234975602244;
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9550000000000000711) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1627210000000000323) ) ) {
                result[0] += 7.905947662588296e-05;
              } else {
                result[0] += 0.0005432617062124779;
              }
            } else {
              result[0] += 0.0002199808965032285;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.005358500000000001283) ) ) {
        result[0] += 0.00041305191736106054;
      } else {
        result[0] += 0.00030952036707862924;
      }
    } else {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
        if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
          result[0] += 0.00026984111755626387;
        } else {
          result[0] += 0.00026984111755626387;
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
          result[0] += 0.00026984111755626387;
        } else {
          result[0] += 0.00026984111755626387;
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.0003884035500857974;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6193272217839197458) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.2416736107842603343) ) ) {
                  result[0] += -0.000496964447073936;
                } else {
                  result[0] += 0.0012152618250526133;
                }
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.045304313006248043) ) ) {
                  result[0] += -0.00041222844212582114;
                } else {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7801862323115579256) ) ) {
                    result[0] += 0.00030382086082879746;
                  } else {
                    result[0] += -0.00041222844212582114;
                  }
                }
              }
            } else {
              result[0] += -0.00041222844212582114;
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
              result[0] += -0.00032666655732795454;
            } else {
              result[0] += 0.0013409545912812899;
            }
          }
        } else {
          result[0] += -0.0004941849366381088;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3450000000000000289) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7240686518592965859) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  result[0] += -0.00014075370306344074;
                } else {
                  result[0] += -0.0018618976078384447;
                }
              } else {
                result[0] += 0.001804895157558494;
              }
            } else {
              result[0] += -0.00046071557621174883;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004848500000000001246) ) ) {
              result[0] += -1.572296334502678e-06;
            } else {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4005449041457286863) ) ) {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.8975410753335467673) ) ) {
                    result[0] += 0.0014936352046614721;
                  } else {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.3597967273366834418) ) ) {
                      result[0] += -0.0022320550215239265;
                    } else {
                      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.07584250000000002101) ) ) {
                        result[0] += -0.0001463229538975545;
                      } else {
                        result[0] += 0.0017349387392985437;
                      }
                    }
                  }
                } else {
                  result[0] += 0.0017328586045628868;
                }
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.3075945000000000484) ) ) {
                  result[0] += 0.0001895912989329395;
                } else {
                  result[0] += 0.000933567429099059;
                }
              }
            }
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
              result[0] += 0.0005213554441732088;
            } else {
              result[0] += 0.00041357045639155176;
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
              result[0] += 0.0001173874316900326;
            } else {
              result[0] += 0.0002046579044010361;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.005358500000000001283) ) ) {
        result[0] += 0.0003956117192806842;
      } else {
        result[0] += 0.0002964515583287507;
      }
    } else {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
        if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
          result[0] += 0.0002584476768225244;
        } else {
          result[0] += 0.0002584476768225244;
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
            result[0] += 0.0002584476768225244;
          } else {
            result[0] += 0.0002584476768225244;
          }
        } else {
          result[0] += 0.0002584476768225244;
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.0003720040744656509;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6193272217839197458) ) ) {
                result[0] += -0.0002810592681781012;
              } else {
                result[0] += -0.00039482301345484215;
              }
            } else {
              result[0] += -0.00039482301345484215;
            }
          } else {
            result[0] += -0.00026517409174771155;
          }
        } else {
          result[0] += -0.0004733190773573426;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4550000000000000711) ) ) {
            result[0] += -0.000249161992931919;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.2273413669989351737) ) ) {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.005458500000000000678) ) ) {
                result[0] += 4.0122087624043715e-05;
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.2030091505812350317) ) ) {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3644477482066475482) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4632663309547739305) ) ) {
                      result[0] += 0.0006682885252945187;
                    } else {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4821784723869347311) ) ) {
                        result[0] += 0.003268669359555814;
                      } else {
                        result[0] += -0.0011578651606277877;
                      }
                    }
                  } else {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5180644051256282356) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
                        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4914057384422110819) ) ) {
                          result[0] += 3.808755060110285e-05;
                        } else {
                          result[0] += 0.0014125947710245457;
                        }
                      } else {
                        result[0] += -0.000797492431027706;
                      }
                    } else {
                      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.2059025000000000161) ) ) {
                        result[0] += 0.0007293385994108623;
                      } else {
                        result[0] += 0.0011826793994263603;
                      }
                    }
                  }
                } else {
                  result[0] += 0.0022856045159887436;
                }
              }
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6247722585678393559) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6169593235427136557) ) ) {
                  result[0] += -0.00034076274387661036;
                } else {
                  result[0] += -0.001824317050828484;
                }
              } else {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7210440605025126848) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.679632490452261373) ) ) {
                    if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.482877277201360311) ) ) {
                      result[0] += 0.0004159267603439981;
                    } else {
                      result[0] += -0.0007894136055329717;
                    }
                  } else {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6800105846231156992) ) ) {
                      result[0] += 0.0045219958104631055;
                    } else {
                      result[0] += 0.0007097933725395619;
                    }
                  }
                } else {
                  result[0] += -0.00016735990039095684;
                }
              }
            }
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
              result[0] += 0.000438378597145372;
            } else {
              result[0] += 0.00038612211708489064;
            }
          } else {
            if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
              result[0] += 0.00011243100859944479;
            } else {
              result[0] += 0.00020205146804857247;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 0.0002475352987708883;
      } else {
        result[0] += 0.0002475352987708883;
      }
    } else {
      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8011796369346734226) ) ) {
        result[0] += 0.0002475352987708883;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
          result[0] += -0.00043307557197670075;
        } else {
          result[0] += 0.0002475352987708883;
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.00035629703021117134;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6193272217839197458) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.2416736107842603343) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5750608109547740154) ) ) {
                    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.071894537606111239) ) ) {
                      result[0] += -0.0014351018451870552;
                    } else {
                      result[0] += 0.00043835485506868595;
                    }
                  } else {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5946878489447237071) ) ) {
                      result[0] += -0.000847265466312604;
                    } else {
                      result[0] += 0.0004194177488614343;
                    }
                  }
                } else {
                  result[0] += 0.0011758172008921033;
                }
              } else {
                if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.4725173572200235816) ) ) {
                  result[0] += -0.0008781142877215582;
                } else {
                  if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.631355564311013695) ) ) {
                    result[0] += 9.510138588541631e-05;
                  } else {
                    result[0] += -0.00037815249027863755;
                  }
                }
              }
            } else {
              result[0] += -0.00037815249027863755;
            }
          } else {
            result[0] += -0.00025397770579359117;
          }
        } else {
          result[0] += -0.00045333423255363955;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3450000000000000289) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7240686518592965859) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.2635054734422110356) ) ) {
                    result[0] += 0.005097818890184826;
                  } else {
                    result[0] += -0.00014470144832018697;
                  }
                } else {
                  result[0] += -0.0017727628137618658;
                }
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9186477097784532253) ) ) {
                  result[0] += 0.000545358103974748;
                } else {
                  result[0] += 0.007099228093044677;
                }
              }
            } else {
              result[0] += -0.000430742575486372;
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.04503850000000000908) ) ) {
              result[0] += 8.596927399856805e-05;
            } else {
              result[0] += 0.00045851936682912844;
            }
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
              result[0] += 0.00041986903636846587;
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
                result[0] += 0.00034339540580099;
              } else {
                result[0] += 0.00040523068807048294;
              }
            }
          } else {
            if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
              result[0] += 0.00010768385944473616;
            } else {
              result[0] += 0.00019352029441860785;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 0.00023708367160007147;
      } else {
        result[0] += 0.00023708367160007147;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            result[0] += 0.00023708367160007147;
          } else {
            result[0] += 0.00023708367160007147;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 0.00023708367160007147;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              result[0] += 0.00023708367160007147;
            } else {
              result[0] += 0.00023708367160007147;
            }
          }
        }
      } else {
        result[0] += 0.00023708367160007147;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.00034125318094875345;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6193272217839197458) ) ) {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.071894537606111239) ) ) {
                  result[0] += -0.0013745078631872164;
                } else {
                  result[0] += 0.00021668721574933042;
                }
              } else {
                result[0] += -0.00036218584284801475;
              }
            } else {
              result[0] += -0.00036218584284801475;
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.05972350000000000575) ) ) {
              result[0] += -0.0002909537594230775;
            } else {
              result[0] += 0.0013062557970052592;
            }
          }
        } else {
          result[0] += -0.00043419320335115426;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4550000000000000711) ) ) {
            result[0] += -0.00022772745756622032;
          } else {
            if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09277402050424696234) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01314200000000000264) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.09250981134579591703) ) ) {
                  if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
                    result[0] += 0.001614473523896201;
                  } else {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5673593061306533292) ) ) {
                      result[0] += 0.00010181901525366833;
                    } else {
                      result[0] += -0.0006772234858003133;
                    }
                  }
                } else {
                  result[0] += 0.0027851216706392653;
                }
              } else {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5131783528140704265) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
                    result[0] += 0.000653326840098209;
                  } else {
                    result[0] += -0.0008922011655358032;
                  }
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.2059025000000000161) ) ) {
                    result[0] += 0.0009971475440072397;
                  } else {
                    result[0] += 0.0012584891978577985;
                  }
                }
              }
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5579756078894474447) ) ) {
                result[0] += -0.0006725209990555833;
              } else {
                result[0] += 3.8903392505506636e-05;
              }
            }
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
              result[0] += 0.0004021410006075717;
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
                result[0] += 0.0003288962989203774;
              } else {
                result[0] += 0.0003881207239929668;
              }
            }
          } else {
            if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
              result[0] += 0.0001031371480996502;
            } else {
              result[0] += 0.0001853493306114508;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 0.00022707334112940367;
      } else {
        result[0] += 0.00022707334112940367;
      }
    } else {
      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8011796369346734226) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            result[0] += 0.00022707334112940367;
          } else {
            result[0] += 0.00022707334112940367;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 0.00022707334112940367;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              result[0] += 0.00022707334112940367;
            } else {
              result[0] += 0.00022707334112940367;
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
          result[0] += -0.0004248002501078266;
        } else {
          result[0] += 0.00022707334112940367;
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.0003268445247456104;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6193272217839197458) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.2416736107842603343) ) ) {
                  result[0] += -0.00045813182782332077;
                } else {
                  result[0] += 0.0011170218005240764;
                }
              } else {
                result[0] += -0.00034689335157589283;
              }
            } else {
              result[0] += -0.00034689335157589283;
            }
          } else {
            result[0] += -0.00023817982016391021;
          }
        } else {
          result[0] += -0.0004158603615137981;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.3450000000000000289) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.394135022639764854) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
                    if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9186477097784532253) ) ) {
                      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
                        result[0] += -9.085827196922325e-05;
                      } else {
                        result[0] += -0.0008314587935829767;
                      }
                    } else {
                      result[0] += 0.0020785285336578953;
                    }
                  } else {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8066186623115578769) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
                        result[0] += -0.0004931222500073392;
                      } else {
                        result[0] += -0.0019399337351134274;
                      }
                    } else {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8168185667587940513) ) ) {
                        result[0] += 0.0014920231581957624;
                      } else {
                        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.07382500000000001561) ) ) {
                          result[0] += -0.0011953545073810413;
                        } else {
                          result[0] += 0.002811974672248102;
                        }
                      }
                    }
                  }
                } else {
                  result[0] += 0.0010642997889484301;
                }
              } else {
                result[0] += -0.0016882965635802232;
              }
            } else {
              result[0] += -0.000618961550970921;
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.04503850000000000908) ) ) {
              result[0] += 7.714464682362878e-05;
            } else {
              result[0] += 0.00041931995172443773;
            }
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
              result[0] += 0.00038516149170795476;
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
                result[0] += 0.00031500938456413574;
              } else {
                result[0] += 0.00037173319007524055;
              }
            }
          } else {
            if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
              result[0] += 9.878241152369071e-05;
            } else {
              result[0] += 0.00017752336756888558;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 0.0002174856745877006;
      } else {
        result[0] += 0.0002174856745877006;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            result[0] += 0.0002174856745877006;
          } else {
            result[0] += 0.0002174856745877006;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 0.0002174856745877006;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              result[0] += 0.0002174856745877006;
            } else {
              result[0] += 0.0002174856745877006;
            }
          }
        }
      } else {
        result[0] += 0.0002174856745877006;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.0003130442419882567;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6193272217839197458) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5946878489447237071) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5750608109547740154) ) ) {
                    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.071894537606111239) ) ) {
                      result[0] += -0.0012971287302554987;
                    } else {
                      result[0] += 0.0005840810934718044;
                    }
                  } else {
                    result[0] += -0.0008012971058690275;
                  }
                } else {
                  result[0] += 0.000821147161572576;
                }
              } else {
                result[0] += -0.000332246551718623;
              }
            } else {
              result[0] += -0.000332246551718623;
            }
          } else {
            result[0] += -0.000228123207259301;
          }
        } else {
          result[0] += -0.00039830158312847096;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.5350000000000001421) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003653500000000000497) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8274453021105528938) ) ) {
                result[0] += -0.00028717142272828865;
              } else {
                result[0] += -0.0006847304748008713;
              }
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                result[0] += 3.0492077573111307e-05;
              } else {
                result[0] += -0.001464382552348405;
              }
            }
          } else {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
              if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3763018001168558224) ) ) {
                if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.4008331129359999911) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4005449041457286863) ) ) {
                    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.212199032544347022) ) ) {
                      result[0] += 0.0024200428340810758;
                    } else {
                      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02214300000000000296) ) ) {
                        result[0] += -0.0004794929521949098;
                      } else {
                        result[0] += 0.0008483746919116036;
                      }
                    }
                  } else {
                    result[0] += 0.0009334004926213665;
                  }
                } else {
                  result[0] += -0.0012123496024063444;
                }
              } else {
                result[0] += 0.003088738232858705;
              }
            } else {
              result[0] += 7.447010022137448e-05;
            }
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
              result[0] += 0.00036889890478852805;
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
                result[0] += 0.000301708814265186;
              } else {
                result[0] += 0.0003560375833113704;
              }
            }
          } else {
            if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
              result[0] += 9.461154400941406e-05;
            } else {
              result[0] += 0.00017002783840132284;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 0.00020830282593108066;
      } else {
        result[0] += 0.00020830282593108066;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            result[0] += 0.00020830282593108066;
          } else {
            result[0] += 0.00020830282593108066;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 0.00020830282593108066;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              result[0] += 0.00020830282593108066;
            } else {
              result[0] += 0.00020830282593108066;
            }
          }
        }
      } else {
        result[0] += 0.00020830282593108066;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.00029982664546170687;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6193272217839197458) ) ) {
                result[0] += -0.00016581195842929258;
              } else {
                result[0] += -0.00031821818039301676;
              }
            } else {
              result[0] += -0.00031821818039301676;
            }
          } else {
            result[0] += -0.0002184912124564415;
          }
        } else {
          result[0] += -0.0003814841850883701;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4550000000000000711) ) ) {
            result[0] += -0.0002027675706977085;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.2273413669989351737) ) ) {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.005458500000000000678) ) ) {
                result[0] += 2.4132157354510205e-05;
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.2030091505812350317) ) ) {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3644477482066475482) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4632663309547739305) ) ) {
                      result[0] += 0.0005844516408890036;
                    } else {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4821784723869347311) ) ) {
                        result[0] += 0.003054131713157003;
                      } else {
                        result[0] += -0.0011272794087465617;
                      }
                    }
                  } else {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5180644051256282356) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
                        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4914057384422110819) ) ) {
                          result[0] += 3.7183083274750613e-06;
                        } else {
                          result[0] += 0.0012876641349331476;
                        }
                      } else {
                        result[0] += -0.0007756335311540362;
                      }
                    } else {
                      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.2059025000000000161) ) ) {
                        result[0] += 0.0006566921446948705;
                      } else {
                        result[0] += 0.0010393973414236203;
                      }
                    }
                  }
                } else {
                  result[0] += 0.00217742588547482;
                }
              }
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6247722585678393559) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6169593235427136557) ) ) {
                  result[0] += -0.0003174336513554137;
                } else {
                  result[0] += -0.0017589633886513534;
                }
              } else {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7210440605025126848) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.679632490452261373) ) ) {
                    if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.482877277201360311) ) ) {
                      result[0] += 0.0003866911126232357;
                    } else {
                      result[0] += -0.0007686978235483903;
                    }
                  } else {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6800105846231156992) ) ) {
                      result[0] += 0.00431939053399618;
                    } else {
                      result[0] += 0.0006681498610358568;
                    }
                  }
                } else {
                  result[0] += -0.00016354183033093523;
                }
              }
            }
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
              result[0] += 0.0003533229694139883;
            } else {
              result[0] += 0.0003153933950459898;
            }
          } else {
            if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
              result[0] += 9.061678209484565e-05;
            } else {
              result[0] += 0.00016284879127368085;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 0.0001995077026251531;
      } else {
        result[0] += 0.0001995077026251531;
      }
    } else {
      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8011796369346734226) ) ) {
        result[0] += 0.0001995077026251531;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
          result[0] += -0.0004248419767823572;
        } else {
          result[0] += 0.0001995077026251531;
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.0002871671325364686;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                result[0] += -0.00030478212583046223;
              } else {
                result[0] += -0.0006584708043345808;
              }
            } else {
              result[0] += -0.00030478212583046223;
            }
          } else {
            result[0] += -0.00020926590720085319;
          }
        } else {
          result[0] += -0.0003653768642581506;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.8950000000000001288) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007303000000000001331) ) ) {
            if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.08500000000000000611) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.03500000000000001027) ) ) {
                result[0] += -5.631422790588871e-06;
              } else {
                result[0] += -0.0007215521261160242;
              }
            } else {
              result[0] += -4.397891615607117e-05;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6754021834779359024) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6722423356281408413) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6642917660552764003) ) ) {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.2203770052010050329) ) ) {
                    result[0] += 0.0037293370122096193;
                  } else {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.08005850000000001854) ) ) {
                      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3197884335317744964) ) ) {
                        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4578754035427136104) ) ) {
                          result[0] += 0.00035711306152133116;
                        } else {
                          result[0] += 0.0028453650584323057;
                        }
                      } else {
                        result[0] += 6.185096506630824e-05;
                      }
                    } else {
                      result[0] += 0.0005936032936708219;
                    }
                  }
                } else {
                  result[0] += -0.001202315364955208;
                }
              } else {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6800105846231156992) ) ) {
                  result[0] += 0.0057876019071305875;
                } else {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.693351338869346745) ) ) {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.04503850000000000908) ) ) {
                      result[0] += -0.0019617970036213983;
                    } else {
                      result[0] += 0.00578603121149886;
                    }
                  } else {
                    result[0] += 0.0011361697597198448;
                  }
                }
              }
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7894192122613066243) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.199891832540424419) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.013855723816631915) ) ) {
                    result[0] += -0.0004099502330192837;
                  } else {
                    result[0] += 0.0017741032290256853;
                  }
                } else {
                  result[0] += -0.0018314600586651695;
                }
              } else {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8507017292462312197) ) ) {
                  result[0] += 0.0012179750488397624;
                } else {
                  result[0] += -0.000608084895169677;
                }
              }
            }
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
              result[0] += 0.0003384046932507984;
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
                result[0] += 0.0002756530466634211;
              } else {
                result[0] += 0.00032768790432993603;
              }
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.156413587100183632) ) ) {
              result[0] += 0.00022986245624884022;
            } else {
              result[0] += 5.888748563380822e-06;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 0.00019108393382976174;
      } else {
        result[0] += 0.00019108393382976174;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        result[0] += 0.00019108393382976174;
      } else {
        result[0] += 0.00019108393382976174;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.00027504213937433377;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                result[0] += -0.00029191337877367305;
              } else {
                result[0] += -0.0006306683398620552;
              }
            } else {
              result[0] += -0.00029191337877367305;
            }
          } else {
            result[0] += -0.00020043011993137487;
          }
        } else {
          result[0] += -0.0003499496392077012;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7750000000000001332) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003653500000000000497) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8254037945979900703) ) ) {
              if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
                result[0] += -0.0002104150595748959;
              } else {
                result[0] += 0.0005312981100214665;
              }
            } else {
              result[0] += -0.000704011155337044;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3197884335317744964) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4632663309547739305) ) ) {
                  result[0] += 0.0004085576653992299;
                } else {
                  result[0] += 0.003536657308292344;
                }
              } else {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4914057384422110819) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4821784723869347311) ) ) {
                        if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2677063317952667609) ) ) {
                          result[0] += -0.0017852041780934671;
                        } else {
                          result[0] += 0.0007352984550927883;
                        }
                      } else {
                        result[0] += -0.0018004349492732076;
                      }
                    } else {
                      result[0] += 0.0029754673401617927;
                    }
                  } else {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5068267582412061545) ) ) {
                      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02678800000000000278) ) ) {
                        result[0] += -0.0042002258847330075;
                      } else {
                        result[0] += -0.0008398362935261288;
                      }
                    } else {
                      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
                        result[0] += 0.003145435700219713;
                      } else {
                        result[0] += -0.0011591160737924368;
                      }
                    }
                  }
                } else {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.009795894273113748066) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5458973873869347182) ) ) {
                      result[0] += 0.00041551165039994064;
                    } else {
                      result[0] += 0.004163942908006167;
                    }
                  } else {
                    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.002753795023577549923) ) ) {
                      result[0] += -0.0018195156340175234;
                    } else {
                      result[0] += 4.091132063980614e-05;
                    }
                  }
                }
              }
            } else {
              result[0] += -0.0013166615225928934;
            }
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.03945373639888280493) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                  result[0] += 0.00034480092954983937;
                } else {
                  result[0] += 0.0005865426962801028;
                }
              } else {
                result[0] += 0.0002779193083190009;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9550000000000000711) ) ) {
                result[0] += 8.469770812779691e-06;
              } else {
                result[0] += 0.0002409094439886815;
              }
            }
          } else {
            result[0] += 5.614438786242272e-05;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 0.00018301583992704151;
      } else {
        result[0] += 0.00018301583992704151;
      }
    } else {
      result[0] += 0.00018301583992704151;
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.00026342909706772774;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4389499174623116007) ) ) {
                  result[0] += 0.0027542477812018394;
                } else {
                  result[0] += -0.0002795879859256006;
                }
              } else {
                result[0] += -0.0006040397725853623;
              }
            } else {
              result[0] += -0.0002795879859256006;
            }
          } else {
            result[0] += -0.0001919674041178055;
          }
        } else {
          result[0] += -0.00033517379440608185;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7750000000000001332) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02741500000000000534) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.2635054734422110356) ) ) {
                  result[0] += 0.00322222931931819;
                } else {
                  result[0] += -7.179105661050164e-05;
                }
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9186477097784532253) ) ) {
                  result[0] += 0.00047529472134336093;
                } else {
                  result[0] += 0.00524771436793655;
                }
              }
            } else {
              result[0] += -0.0019656441577089777;
            }
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.735388073517588059) ) ) {
              if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8440161800932387548) ) ) {
                result[0] += -0.00021865676806796035;
              } else {
                result[0] += -0.0020874417270746568;
              }
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7403451809045227261) ) ) {
                result[0] += 0.0009547764968591888;
              } else {
                result[0] += -0.0002527469177406351;
              }
            }
          }
        } else {
          if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1701831610694422292) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004848500000000001246) ) ) {
                  result[0] += 7.016740409571457e-05;
                } else {
                  result[0] += 0.0005243822608164289;
                }
              } else {
                result[0] += 0.00026303499489412253;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9550000000000000711) ) ) {
                result[0] += 6.0773176863010276e-05;
              } else {
                result[0] += 0.00023073757879207645;
              }
            }
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5126512388693468258) ) ) {
              result[0] += -0.0001279819762622662;
            } else {
              if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.03945373639888280493) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03566000000000000419) ) ) {
                  result[0] += 0.00023073757879207645;
                } else {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1068140077680278383) ) ) {
                    result[0] += -0.0005492421660118663;
                  } else {
                    result[0] += 0.00031788007589099324;
                  }
                }
              } else {
                result[0] += 6.441168707449055e-05;
              }
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 0.00017528840333609944;
      } else {
        result[0] += 0.00017528840333609944;
      }
    } else {
      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8011796369346734226) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          result[0] += 0.00017528840333609944;
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 0.00017528840333609944;
          } else {
            result[0] += 0.00017528840333609944;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
          result[0] += -0.00042269950017202024;
        } else {
          result[0] += 0.00017528840333609944;
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.00025230638963097776;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)4.143697683123688691) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)3.083217571286521075) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9189305784170854752) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                    result[0] += -0.00026778300536386295;
                  } else {
                    result[0] += -0.0003210218267717481;
                  }
                } else {
                  result[0] += 1.2913283219646038e-06;
                }
              } else {
                result[0] += -0.00026778300536386295;
              }
            } else {
              result[0] += -0.00037254208947555464;
            }
          } else {
            result[0] += 1.2913283219646038e-06;
          }
        } else {
          result[0] += -0.00020311870844326078;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9150000000000001465) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007303000000000001331) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8254037945979900703) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8145641537437187107) ) ) {
                if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.08500000000000000611) ) ) {
                  result[0] += -0.00036819072969789836;
                } else {
                  result[0] += -3.9003780227972954e-05;
                }
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002861500000000000328) ) ) {
                  result[0] += 0.0009566388217581636;
                } else {
                  result[0] += 0.004350792546095246;
                }
              }
            } else {
              result[0] += -0.0005576090632369243;
            }
          } else {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3197884335317744964) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4578754035427136104) ) ) {
                if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.4612588522637047217) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
                    result[0] += 0.00048254676001733876;
                  } else {
                    result[0] += 0.002161017451455171;
                  }
                } else {
                  result[0] += -0.0005613397376826986;
                }
              } else {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4821784723869347311) ) ) {
                  result[0] += 0.0029567058459743925;
                } else {
                  result[0] += -0.0009432375939664276;
                }
              }
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5180644051256282356) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4839721393467337207) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4821784723869347311) ) ) {
                      result[0] += 4.1059160855698486e-05;
                    } else {
                      result[0] += -0.002401768151135198;
                    }
                  } else {
                    result[0] += 0.0010835782129713198;
                  }
                } else {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5068267582412061545) ) ) {
                    result[0] += -0.002323422816976272;
                  } else {
                    result[0] += -0.0002313555030605813;
                  }
                }
              } else {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.009795894273113748066) ) ) {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.0841877145549009831) ) ) {
                    result[0] += 0.00028179754939489435;
                  } else {
                    result[0] += 0.0020207190138626526;
                  }
                } else {
                  result[0] += 7.41125039602873e-05;
                }
              }
            }
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
              result[0] += 0.0002400442433619041;
            } else {
              result[0] += 0.0002704314917758063;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.07127303416489440269) ) ) {
              result[0] += 0.00021731579993976568;
            } else {
              result[0] += 2.1763183554010854e-06;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 0.0001678872405599858;
      } else {
        result[0] += 0.0001678872405599858;
      }
    } else {
      result[0] += 0.0001678872405599858;
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.0002416533137653056;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.009542500000000000634) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                result[0] += -0.0002564764638376999;
              } else {
                result[0] += -0.0002564764638376999;
              }
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                result[0] += 1.2368048570555288e-06;
              } else {
                result[0] += -0.0005252218015431018;
              }
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.555383890033505745) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7664523331407036011) ) ) {
                result[0] += -0.00022015670475368222;
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.07584250000000002101) ) ) {
                  result[0] += -0.0006423844431450283;
                } else {
                  result[0] += -0.00022015670475368222;
                }
              }
            } else {
              result[0] += -0.00032107635023665717;
            }
          }
        } else {
          result[0] += -0.00019454247296247018;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9150000000000001465) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.4550000000000000711) ) ) {
            result[0] += -0.00018234298714084644;
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
                if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4750000000000000333) ) ) {
                  result[0] += -9.913477101235038e-05;
                } else {
                  result[0] += 0.0014865875154636845;
                }
              } else {
                result[0] += -0.00024716078398465715;
              }
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.7308248862661052003) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6722423356281408413) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.482877277201360311) ) ) {
                    result[0] += 0.00026614991489281415;
                  } else {
                    result[0] += -0.000965683926827456;
                  }
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01030150000000000163) ) ) {
                    result[0] += 0.0006104230296094587;
                  } else {
                    result[0] += 0.001403743952423199;
                  }
                }
              } else {
                result[0] += -0.0001350936787491026;
              }
            }
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
              result[0] += 0.00022990890933650686;
            } else {
              result[0] += 0.000259013123804354;
            }
          } else {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2450759342279490716) ) ) {
              result[0] += 0.00021181952189116852;
            } else {
              result[0] += 3.9579566840484e-05;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 0.00016079857541290312;
      } else {
        result[0] += 0.00016079857541290312;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 0.00016079857541290312;
            } else {
              result[0] += 0.00016079857541290312;
            }
          } else {
            result[0] += 0.00016079857541290312;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 0.00016079857541290312;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 0.00016079857541290312;
              } else {
                result[0] += 0.00016079857541290312;
              }
            } else {
              result[0] += 0.00016079857541290312;
            }
          }
        }
      } else {
        result[0] += 0.00016079857541290312;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.00023145004032265476;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.009542500000000000634) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                result[0] += -0.0002456473158679694;
              } else {
                result[0] += -0.0002456473158679694;
              }
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                result[0] += 1.1845835241256923e-06;
              } else {
                result[0] += -0.0005030454797054852;
              }
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.555383890033505745) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7664523331407036011) ) ) {
                result[0] += -0.00021086107779192496;
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.07584250000000002101) ) ) {
                  result[0] += -0.0006152611894780854;
                } else {
                  result[0] += -0.00021086107779192496;
                }
              }
            } else {
              result[0] += -0.0003075196158125034;
            }
          }
        } else {
          result[0] += -0.00018632834994087005;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7750000000000001332) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.29500000000000004) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.03500000000000001027) ) ) {
              result[0] += 9.186977064850185e-05;
            } else {
              result[0] += -0.00034610655492450066;
            }
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)4.300000000000000843e-05) ) ) {
              result[0] += 0.000845985668492263;
            } else {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002091500000000000477) ) ) {
                result[0] += -0.0003276678203647407;
              } else {
                result[0] += 0.00012258181620024855;
              }
            }
          }
        } else {
          if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1701831610694422292) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004848500000000001246) ) ) {
                  result[0] += 4.974931629959472e-05;
                } else {
                  result[0] += 0.0004709457010690154;
                }
              } else {
                result[0] += 0.00023208620141979943;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9550000000000000711) ) ) {
                result[0] += 4.141529970432055e-05;
              } else {
                result[0] += 0.0002028759139237376;
              }
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9650000000000000799) ) ) {
              result[0] += 0.0005286978450713629;
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5126512388693468258) ) ) {
                result[0] += -0.00017214316202846392;
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.09683050000000001378) ) ) {
                  result[0] += 2.9428726280435688e-05;
                } else {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
                    result[0] += 0.0003745906428450487;
                  } else {
                    result[0] += -0.00024960749468302013;
                  }
                }
              }
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 0.00015400921337783275;
      } else {
        result[0] += 0.00015400921337783275;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            result[0] += 0.00015400921337783275;
          } else {
            result[0] += 0.00015400921337783275;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 0.00015400921337783275;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              result[0] += 0.00015400921337783275;
            } else {
              result[0] += 0.00015400921337783275;
            }
          }
        }
      } else {
        result[0] += 0.00015400921337783275;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.0002216775773966212;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.009542500000000000634) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                result[0] += -0.00023527540457405534;
              } else {
                result[0] += -0.00023527540457405534;
              }
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                result[0] += 1.1345671207750145e-06;
              } else {
                result[0] += -0.00048180550371033107;
              }
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.555383890033505745) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7664523331407036011) ) ) {
                result[0] += -0.00020195793799383964;
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.07584250000000002101) ) ) {
                  result[0] += -0.000589283154842101;
                } else {
                  result[0] += -0.00020195793799383964;
                }
              }
            } else {
              result[0] += -0.00029453528433273207;
            }
          }
        } else {
          result[0] += -0.0001784610499856498;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.7750000000000001332) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01626400000000000415) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8254037945979900703) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8145641537437187107) ) ) {
                if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
                    result[0] += -0.00013084864644829589;
                  } else {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8066186623115578769) ) ) {
                      result[0] += -0.0018416960728909525;
                    } else {
                      result[0] += -0.00024305454356185805;
                    }
                  }
                } else {
                  result[0] += 0.0004997556267294192;
                }
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004748500000000000117) ) ) {
                  result[0] += 0.0010135312985445348;
                } else {
                  result[0] += 0.007283370974833222;
                }
              }
            } else {
              result[0] += -0.000551849232516119;
            }
          } else {
            result[0] += 0.0002041244658227883;
          }
        } else {
          if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1701831610694422292) ) ) {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007599500000000001219) ) ) {
                  result[0] += 0.0001253433478344351;
                } else {
                  result[0] += 0.00045106106679781093;
                }
              } else {
                result[0] += 0.00022228687800703584;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9550000000000000711) ) ) {
                result[0] += 3.9666630832337515e-05;
              } else {
                result[0] += 0.0001943099299012622;
              }
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9650000000000000799) ) ) {
              result[0] += 0.0005063747550307167;
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5126512388693468258) ) ) {
                result[0] += -0.00016487480006771986;
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.09683050000000001378) ) ) {
                  result[0] += 2.8186163798550167e-05;
                } else {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
                    result[0] += 0.0003587743864964246;
                  } else {
                    result[0] += -0.0002390683736508967;
                  }
                }
              }
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 0.0001475065170468912;
      } else {
        result[0] += 0.0001475065170468912;
      }
    } else {
      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8011796369346734226) ) ) {
        result[0] += 0.0001475065170468912;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
          result[0] += -0.00042523267788851176;
        } else {
          result[0] += 0.0001475065170468912;
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      result[0] += -0.0002123177349717876;
    } else {
      if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.009542500000000000634) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                result[0] += -0.00022534142415477234;
              } else {
                result[0] += -0.00022534142415477234;
              }
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
                result[0] += 1.0866625487584623e-06;
              } else {
                result[0] += -0.00046146233843801426;
              }
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.555383890033505745) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7664523331407036011) ) ) {
                result[0] += -0.00019343071346230944;
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.07584250000000002101) ) ) {
                  result[0] += -0.0005644019849118538;
                } else {
                  result[0] += -0.00019343071346230944;
                }
              }
            } else {
              result[0] += -0.0002820991873567375;
            }
          }
        } else {
          result[0] += -0.00017092592926458804;
        }
      } else {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9150000000000001465) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.007303000000000001331) ) ) {
            if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.08500000000000000611) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.03500000000000001027) ) ) {
                result[0] += 4.027109949383133e-05;
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0002825000000000000362) ) ) {
                  if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1550000000000000266) ) ) {
                    result[0] += -0.0005921259817545778;
                  } else {
                    result[0] += 0.000998849528318403;
                  }
                } else {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
                    result[0] += 0.0005053742268452879;
                  } else {
                    result[0] += -0.001247131121430952;
                  }
                }
              }
            } else {
              result[0] += -3.418714297339852e-05;
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7240686518592965859) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7210440605025126848) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7077536600502513098) ) ) {
                    if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                      result[0] += 0.00024402207255073643;
                    } else {
                      result[0] += -0.0019293536030320132;
                    }
                  } else {
                    result[0] += 0.0024157140208871464;
                  }
                } else {
                  result[0] += -0.0010542593935482826;
                }
              } else {
                result[0] += 0.0024216804180224247;
              }
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7382388927638191545) ) ) {
                result[0] += -0.0014340291038080308;
              } else {
                result[0] += -0.00010316613461692886;
              }
            }
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9650000000000000799) ) ) {
              result[0] += 0.0002029859341650933;
            } else {
              result[0] += 0.00023199096149902778;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.08693186820944626136) ) ) {
              result[0] += 0.0001861056254929646;
            } else {
              result[0] += -3.6458126061631704e-06;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 0.0001412783825986131;
      } else {
        result[0] += 0.0001412783825986131;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          result[0] += 0.0001412783825986131;
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 0.0001412783825986131;
          } else {
            result[0] += 0.0001412783825986131;
          }
        }
      } else {
        result[0] += 0.0001412783825986131;
      }
    }
  }
}

