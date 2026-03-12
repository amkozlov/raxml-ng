
#include "header.h"

void predict_unit9(union Entry* data, double* result) {
  unsigned int tmp;
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5126512388693468258) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 2.2366681687397747e-06;
        } else {
          result[0] += -1.3044776458352992e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 2.2366681687397747e-06;
          } else {
            result[0] += -5.1134611995603414e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.483243480726212482) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5131783528140704265) ) ) {
              result[0] += -0.0025658263474201636;
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5645244997236181783) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01911900000000000405) ) ) {
                  result[0] += 0.0003657490747075238;
                } else {
                  result[0] += 0.002272322597445209;
                }
              } else {
                if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1243100835431067558) ) ) {
                  result[0] += -0.0008763633382895951;
                } else {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7568047583165830039) ) ) {
                    result[0] += -8.966605405052192e-06;
                  } else {
                    if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.013855723816631915) ) ) {
                      result[0] += -5.427123783240292e-05;
                    } else {
                      result[0] += -5.05043344082396e-05;
                    }
                  }
                }
              }
            }
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
              result[0] += -7.977779739453912e-05;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8099155601256282644) ) ) {
                      result[0] += 0.00036880102489591837;
                    } else {
                      result[0] += -5.427123783240292e-05;
                    }
                  } else {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                      result[0] += 4.353380397164283e-05;
                    } else {
                      result[0] += -6.720850916105239e-05;
                    }
                  }
                } else {
                  result[0] += -5.427123783240292e-05;
                }
              } else {
                result[0] += 2.617118527960038e-07;
              }
            }
          }
        }
      }
    } else {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.4612588522637047217) ) ) {
        if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5303668681866521295) ) ) {
          result[0] += 4.4362064819864116e-05;
        } else {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0008435000000000001741) ) ) {
            result[0] += -0.0006336619940033093;
          } else {
            result[0] += 0.0004031383010918549;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4138030768592965147) ) ) {
          result[0] += -0.0004226298659740898;
        } else {
          result[0] += 9.733722938377729e-06;
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 3.40254914574387e-05;
      } else {
        result[0] += 3.40254914574387e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 3.40254914574387e-05;
            } else {
              result[0] += 3.40254914574387e-05;
            }
          } else {
            result[0] += 3.40254914574387e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 3.40254914574387e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 3.40254914574387e-05;
              } else {
                result[0] += 3.40254914574387e-05;
              }
            } else {
              result[0] += 3.40254914574387e-05;
            }
          }
        }
      } else {
        result[0] += 3.40254914574387e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5126512388693468258) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 2.1422298323870117e-06;
        } else {
          result[0] += -1.2493989799858565e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 2.1422298323870117e-06;
          } else {
            result[0] += -4.897556678970275e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.483243480726212482) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5131783528140704265) ) ) {
              result[0] += -0.002457490039421044;
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5645244997236181783) ) ) {
                result[0] += 0.0005293823589117987;
              } else {
                if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1243100835431067558) ) ) {
                  if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.05539262878325219158) ) ) {
                    result[0] += 0.0010704756430343749;
                  } else {
                    result[0] += -0.001010890686724594;
                  }
                } else {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7568047583165830039) ) ) {
                    result[0] += -8.588010444467678e-06;
                  } else {
                    if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.013855723816631915) ) ) {
                      result[0] += -5.197975558021686e-05;
                    } else {
                      result[0] += -4.837190127096089e-05;
                    }
                  }
                }
              }
            }
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
              result[0] += -7.640935742247468e-05;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8099155601256282644) ) ) {
                      result[0] += 0.00035322922228204004;
                    } else {
                      result[0] += -5.197975558021686e-05;
                    }
                  } else {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                      result[0] += 4.169568597110579e-05;
                    } else {
                      result[0] += -6.437077941525167e-05;
                    }
                  }
                } else {
                  result[0] += -5.197975558021686e-05;
                }
              } else {
                result[0] += 2.50661652177386e-07;
              }
            }
          }
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.7760221401809592745) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6722423356281408413) ) ) {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.527988611169282529) ) ) {
            result[0] += 2.6827389705004214e-05;
          } else {
            result[0] += -0.0009435451754624773;
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02972700000000000342) ) ) {
            result[0] += 0.0003490070201988625;
          } else {
            result[0] += 0.0006651466775756628;
          }
        }
      } else {
        result[0] += -9.869339283916533e-05;
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 3.258884079475252e-05;
      } else {
        result[0] += 3.258884079475252e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 3.258884079475252e-05;
            } else {
              result[0] += 3.258884079475252e-05;
            }
          } else {
            result[0] += 3.258884079475252e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 3.258884079475252e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 3.258884079475252e-05;
              } else {
                result[0] += 3.258884079475252e-05;
              }
            } else {
              result[0] += 3.258884079475252e-05;
            }
          }
        }
      } else {
        result[0] += 3.258884079475252e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5126512388693468258) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 2.0517789446409272e-06;
        } else {
          result[0] += -1.1966458882399576e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 2.0517789446409272e-06;
          } else {
            result[0] += -4.690768246327685e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.483243480726212482) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5131783528140704265) ) ) {
              result[0] += -0.00235372799095538;
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5645244997236181783) ) ) {
                result[0] += 0.0005070303667974317;
              } else {
                if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1243100835431067558) ) ) {
                  result[0] += -0.0008845592984154212;
                } else {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
                    result[0] += -8.225400813637873e-06;
                  } else {
                    if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.992027305872230758) ) ) {
                      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9774026691300493619) ) ) {
                        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7640286906783920751) ) ) {
                          result[0] += -4.978502606708385e-05;
                        } else {
                          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8639185851088165835) ) ) {
                            if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.803731059838205808) ) ) {
                              result[0] += -0.0012446576401858034;
                            } else {
                              result[0] += 0.0020613537445356932;
                            }
                          } else {
                            result[0] += -4.978502606708385e-05;
                          }
                        }
                      } else {
                        result[0] += -0.0005821746356453699;
                      }
                    } else {
                      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.786764172562814168) ) ) {
                        result[0] += 0.00025883445720607334;
                      } else {
                        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7968587857286433263) ) ) {
                          result[0] += -0.00014227387340984515;
                        } else {
                          result[0] += -5.009640880194036e-05;
                        }
                      }
                    }
                  }
                }
              }
            }
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
              result[0] += -7.31831423327204e-05;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                    result[0] += -4.978502606708385e-05;
                  } else {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                      result[0] += 3.9935178412929805e-05;
                    } else {
                      result[0] += -6.165286649340258e-05;
                    }
                  }
                } else {
                  result[0] += -4.978502606708385e-05;
                }
              } else {
                result[0] += 2.4007802169079384e-07;
              }
            }
          }
        }
      }
    } else {
      result[0] += 1.2455684310687355e-05;
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 3.1212849509442045e-05;
      } else {
        result[0] += 3.1212849509442045e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 3.1212849509442045e-05;
            } else {
              result[0] += 3.1212849509442045e-05;
            }
          } else {
            result[0] += 3.1212849509442045e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 3.1212849509442045e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 3.1212849509442045e-05;
              } else {
                result[0] += 3.1212849509442045e-05;
              }
            } else {
              result[0] += 3.1212849509442045e-05;
            }
          }
        }
      } else {
        result[0] += 3.1212849509442045e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5126512388693468258) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 1.965147144357086e-06;
        } else {
          result[0] += -1.146120178405905e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 1.965147144357086e-06;
          } else {
            result[0] += -4.49271099510427e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.483243480726212482) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5131783528140704265) ) ) {
              result[0] += -0.0022543470640930935;
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01911900000000000405) ) ) {
                  if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.4725173572200235816) ) ) {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5809002386432161602) ) ) {
                      result[0] += 0.0001388777907797199;
                    } else {
                      result[0] += -0.0004032781267826588;
                    }
                  } else {
                    result[0] += 3.0471080463094724e-05;
                  }
                } else {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5525538534170856275) ) ) {
                    result[0] += 0.002557531448711057;
                  } else {
                    result[0] += 0.00038589925576619093;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.992027305872230758) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9774026691300493619) ) ) {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7640286906783920751) ) ) {
                      result[0] += -4.76829641238932e-05;
                    } else {
                      if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8639185851088165835) ) ) {
                        if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.803731059838205808) ) ) {
                          result[0] += -0.0011921047409624384;
                        } else {
                          result[0] += 0.0019743176696323016;
                        }
                      } else {
                        result[0] += -4.76829641238932e-05;
                      }
                    }
                  } else {
                    result[0] += -0.000557593607120206;
                  }
                } else {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.786764172562814168) ) ) {
                    result[0] += 0.0002479057482134103;
                  } else {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7968587857286433263) ) ) {
                      result[0] += -0.00013626667569537228;
                    } else {
                      result[0] += -4.798119941566459e-05;
                    }
                  }
                }
              }
            }
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
              result[0] += -7.009314699610198e-05;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
                  result[0] += -4.76829641238932e-05;
                } else {
                  result[0] += -4.76829641238932e-05;
                }
              } else {
                result[0] += 2.2994126145062238e-07;
              }
            }
          }
        }
      }
    } else {
      result[0] += 1.1929770757268175e-05;
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 2.989495639427173e-05;
      } else {
        result[0] += 2.989495639427173e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 2.989495639427173e-05;
            } else {
              result[0] += 2.989495639427173e-05;
            }
          } else {
            result[0] += 2.989495639427173e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 2.989495639427173e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 2.989495639427173e-05;
              } else {
                result[0] += 2.989495639427173e-05;
              }
            } else {
              result[0] += 2.989495639427173e-05;
            }
          }
        }
      } else {
        result[0] += 2.989495639427173e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 1.8821731790656637e-06;
        } else {
          result[0] += 5.181633754497123e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 1.8821731790656637e-06;
          } else {
            result[0] += -4.3030162705933795e-05;
          }
        } else {
          if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1701831610694422292) ) ) {
              result[0] += 0.00012961160045345604;
            } else {
              if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4150000000000000355) ) ) {
                result[0] += -0.001966527906441572;
              } else {
                result[0] += -0.00018381808368658116;
              }
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6722423356281408413) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.527988611169282529) ) ) {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02621450000000000516) ) ) {
                    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.05751864358971629093) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5556488633165830304) ) ) {
                        result[0] += 0.0006944948214152646;
                      } else {
                        result[0] += -0.0006427381316028349;
                      }
                    } else {
                      result[0] += -7.906291688878638e-05;
                    }
                  } else {
                    if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
                      result[0] += -0.0004584900989198879;
                    } else {
                      result[0] += 0.0002267175305026602;
                    }
                  }
                } else {
                  if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.04500000000000000527) ) ) {
                    result[0] += 0.0003351989242658939;
                  } else {
                    result[0] += -0.0010318252546985957;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.482877277201360311) ) ) {
                  if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1995315939937592209) ) ) {
                    result[0] += 0.00290411611390655;
                  } else {
                    result[0] += -0.0013416906776413998;
                  }
                } else {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6828811456281408399) ) ) {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003977500000000001) ) ) {
                      result[0] += 5.204240376353904e-05;
                    } else {
                      result[0] += 0.0020729908423820706;
                    }
                  } else {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7240686518592965859) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7210440605025126848) ) ) {
                        result[0] += 0.00025370671291312976;
                      } else {
                        result[0] += -0.00029860405632726317;
                      }
                    } else {
                      result[0] += 0.0007865521640154528;
                    }
                  }
                }
              }
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.735388073517588059) ) ) {
                result[0] += -0.0006758595689774643;
              } else {
                result[0] += -4.566965706870956e-05;
              }
            }
          }
        }
      }
    } else {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
        result[0] += -6.713361983666177e-05;
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -4.3030162705933795e-05;
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8323869080904523488) ) ) {
                result[0] += 0.0001824700812477485;
              } else {
                result[0] += -4.566965706870956e-05;
              }
            } else {
              result[0] += -4.566965706870956e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0005965000000000001334) ) ) {
            result[0] += 2.2023250335509978e-07;
          } else {
            result[0] += -0.000310564760441433;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 2.863270838329216e-05;
      } else {
        result[0] += 2.863270838329216e-05;
      }
    } else {
      result[0] += 2.863270838329216e-05;
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 1.8027026048235482e-06;
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4891798216080402439) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4795216591959799435) ) ) {
              result[0] += 5.32487870068536e-05;
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.06983950000000001268) ) ) {
                result[0] += -0.0007905829635629206;
              } else {
                result[0] += 0.0001549078082338918;
              }
            }
          } else {
            result[0] += 0.00026119470274870875;
          }
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 1.8027026048235482e-06;
          } else {
            result[0] += -4.121330983713019e-05;
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5068267582412061545) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.04215400000000000397) ) ) {
              if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.09688331830159578606) ) ) {
                result[0] += -0.002205981245343382;
              } else {
                result[0] += -0.0002463878068859378;
              }
            } else {
              result[0] += 0.000150822922396639;
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1450000000000000455) ) ) {
              result[0] += -4.374135742388575e-05;
            } else {
              result[0] += 3.3037572477170976e-05;
            }
          }
        }
      }
    } else {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += -6.429905212593843e-05;
        } else {
          result[0] += -0.0008299539989705697;
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -4.121330983713019e-05;
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8323869080904523488) ) ) {
                if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002861500000000000328) ) ) {
                    result[0] += -6.361574183617198e-05;
                  } else {
                    result[0] += 0.006592416540211408;
                  }
                } else {
                  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5950000000000000844) ) ) {
                    result[0] += 0.0012416168002209703;
                  } else {
                    result[0] += -0.0005787407732502117;
                  }
                }
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.055261500000000012) ) ) {
                  result[0] += -4.374135742388575e-05;
                } else {
                  result[0] += 0.00014790606822922888;
                }
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2250000000000000333) ) ) {
                result[0] += -4.374135742388575e-05;
              } else {
                result[0] += 0.0006764295920902824;
              }
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0005965000000000001334) ) ) {
            result[0] += 2.1093367596606595e-07;
          } else {
            result[0] += -0.00029745185450581307;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 2.742375598580129e-05;
      } else {
        result[0] += 2.742375598580129e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            result[0] += 2.742375598580129e-05;
          } else {
            result[0] += 2.742375598580129e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 2.742375598580129e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              result[0] += 2.742375598580129e-05;
            } else {
              result[0] += 2.742375598580129e-05;
            }
          }
        }
      } else {
        result[0] += 2.742375598580129e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4992188184422110542) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 1.7265874987395539e-06;
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4891798216080402439) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4795216591959799435) ) ) {
              result[0] += 5.1000475465601264e-05;
            } else {
              result[0] += -0.00044543542542260816;
            }
          } else {
            result[0] += 0.0004556227220735451;
          }
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 1.7265874987395539e-06;
          } else {
            result[0] += -3.94731695378197e-05;
          }
        } else {
          if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1044543990012605922) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1701831610694422292) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2545696998002126565) ) ) {
                result[0] += -0.0006864122533755967;
              } else {
                result[0] += 0.00030443392660296645;
              }
            } else {
              if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.4150000000000000355) ) ) {
                result[0] += -0.0018320461222441904;
              } else {
                if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.00217550000000000035) ) ) {
                  result[0] += 0.0011220842649440448;
                } else {
                  result[0] += -0.00034887060932302697;
                }
              }
            }
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5531655541959800138) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5458973873869347182) ) ) {
                result[0] += -3.214039417169725e-06;
              } else {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.009795894273113748066) ) ) {
                  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9750000000000000888) ) ) {
                    result[0] += 0.0013986991920839887;
                  } else {
                    result[0] += -6.466882972489765e-05;
                  }
                } else {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.08390973343508316418) ) ) {
                    result[0] += -0.00028418515257781757;
                  } else {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5499504253266332965) ) ) {
                      result[0] += 0.0004301084782804168;
                    } else {
                      result[0] += 0.003301231446306405;
                    }
                  }
                }
              }
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5579756078894474447) ) ) {
                result[0] += -0.002644612913828799;
              } else {
                if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1414455000000000295) ) ) {
                  result[0] += -3.765948791137857e-05;
                } else {
                  if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6754021834779359024) ) ) {
                    result[0] += 0.0004137666122005835;
                  } else {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
                      result[0] += -0.0003340260556866742;
                    } else {
                      result[0] += 0.0033502509016335147;
                    }
                  }
                }
              }
            }
          }
        }
      }
    } else {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += -6.158416772927181e-05;
        } else {
          result[0] += -0.000794911038191879;
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -3.94731695378197e-05;
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8323869080904523488) ) ) {
                result[0] += 0.000152604902045512;
              } else {
                result[0] += -4.189447594067925e-05;
              }
            } else {
              result[0] += -4.189447594067925e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0005965000000000001334) ) ) {
            result[0] += 2.0202747087162424e-07;
          } else {
            result[0] += -0.00028489261184426196;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 2.626584891310964e-05;
      } else {
        result[0] += 2.626584891310964e-05;
      }
    } else {
      result[0] += 2.626584891310964e-05;
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 1.6536861836373316e-06;
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4891798216080402439) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4795216591959799435) ) ) {
              result[0] += 4.884709387619796e-05;
            } else {
              result[0] += -0.00042662790577466865;
            }
          } else {
            result[0] += 0.00023811696702917537;
          }
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 1.6536861836373316e-06;
          } else {
            result[0] += -3.780650279045763e-05;
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5068267582412061545) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.04215400000000000397) ) ) {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003120500000000000444) ) ) {
                result[0] += 0.00024235804508930935;
              } else {
                result[0] += -0.0019160733344969056;
              }
            } else {
              result[0] += 0.00016063935413129288;
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1450000000000000455) ) ) {
              result[0] += -4.030438786415825e-05;
            } else {
              result[0] += 3.076022735004003e-05;
            }
          }
        }
      }
    } else {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += -5.898391328504721e-05;
        } else {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
            result[0] += 6.314091075865775e-05;
          } else {
            result[0] += -0.0013959470108921414;
          }
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -3.780650279045763e-05;
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  result[0] += -4.012557491838887e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                    result[0] += 4.580639357439058e-05;
                  } else {
                    result[0] += -5.1492322191227915e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8323869080904523488) ) ) {
                  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5950000000000000844) ) ) {
                    result[0] += 0.0013883763752526087;
                  } else {
                    result[0] += -0.0005607481343334233;
                  }
                } else {
                  result[0] += -0.0002951438915582324;
                }
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2250000000000000333) ) ) {
                result[0] += -4.012557491838887e-05;
              } else {
                result[0] += 0.0006496377587892632;
              }
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0005965000000000001334) ) ) {
            result[0] += 1.934973104690554e-07;
          } else {
            result[0] += -0.00027286365525705324;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 2.515683188997148e-05;
      } else {
        result[0] += 2.515683188997148e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            result[0] += 2.515683188997148e-05;
          } else {
            result[0] += 2.515683188997148e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 2.515683188997148e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              result[0] += 2.515683188997148e-05;
            } else {
              result[0] += 2.515683188997148e-05;
            }
          }
        }
      } else {
        result[0] += 2.515683188997148e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 1.5838629643440664e-06;
        } else {
          result[0] += 4.1984394799605046e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 1.5838629643440664e-06;
          } else {
            result[0] += -3.6210207337807514e-05;
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5068267582412061545) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.04215400000000000397) ) ) {
              if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003120500000000000444) ) ) {
                result[0] += 0.00023212501593468222;
              } else {
                result[0] += -0.0018351714016269477;
              }
            } else {
              result[0] += 0.000153856714860541;
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8643464628140704598) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1450000000000000455) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9033411549107539518) ) ) {
                    if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8299222285691966183) ) ) {
                      result[0] += -6.566755453899153e-05;
                    } else {
                      result[0] += -0.00032292000599067777;
                    }
                  } else {
                    if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9186477097784532253) ) ) {
                      result[0] += 0.0031109598468984983;
                    } else {
                      result[0] += 0.00017566294010132961;
                    }
                  }
                } else {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7640286906783920751) ) ) {
                    if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.966590843157139501) ) ) {
                      if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.803731059838205808) ) ) {
                        result[0] += 0.0009638372171874568;
                      } else {
                        result[0] += -0.00021962749996921391;
                      }
                    } else {
                      result[0] += 7.102985375135129e-05;
                    }
                  } else {
                    if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.803731059838205808) ) ) {
                      result[0] += -0.0013562987934785402;
                    } else {
                      if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8639185851088165835) ) ) {
                        result[0] += 0.0016869096230949475;
                      } else {
                        result[0] += -3.860262477260777e-05;
                      }
                    }
                  }
                }
              } else {
                result[0] += 2.579605662925689e-05;
              }
            } else {
              result[0] += 0.0013375200081239757;
            }
          }
        }
      }
    } else {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += -5.6493448798599314e-05;
        } else {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
            result[0] += 6.0474926304108576e-05;
          } else {
            result[0] += -0.001337006254642398;
          }
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -3.6210207337807514e-05;
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                result[0] += -3.843136180557587e-05;
              } else {
                result[0] += -4.221532008934133e-05;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2250000000000000333) ) ) {
                result[0] += -3.843136180557587e-05;
              } else {
                result[0] += 0.0006222082500094433;
              }
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0005965000000000001334) ) ) {
            result[0] += 1.8532731710802607e-07;
          } else {
            result[0] += -0.0002613425945946993;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 2.4094640642830242e-05;
      } else {
        result[0] += 2.4094640642830242e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        result[0] += 2.4094640642830242e-05;
      } else {
        result[0] += 2.4094640642830242e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5042218989698493692) ) ) {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += 1.5169878751136335e-06;
        } else {
          result[0] += 4.021169715358435e-05;
        }
      } else {
        if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
            result[0] += 1.5169878751136335e-06;
          } else {
            result[0] += -3.4681311908541654e-05;
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5068267582412061545) ) ) {
            result[0] += -0.0010616700382276177;
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1450000000000000455) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7478339930150754711) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9033411549107539518) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8299222285691966183) ) ) {
                    result[0] += -6.289488817314881e-05;
                  } else {
                    result[0] += -0.0003092854273048447;
                  }
                } else {
                  result[0] += 0.00039612374890044975;
                }
              } else {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8066186623115578769) ) ) {
                  result[0] += -3.697271484080565e-05;
                } else {
                  result[0] += 0.00012048413394357114;
                }
              }
            } else {
              result[0] += 2.8372264109026304e-05;
            }
          }
        }
      }
    } else {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += -5.410813863326749e-05;
        } else {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.50000000000000025e-06) ) ) {
            result[0] += 5.7921507110758465e-05;
          } else {
            result[0] += -0.0012805541406693205;
          }
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -3.4681311908541654e-05;
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  result[0] += -3.680868307145939e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                    result[0] += 4.549499926899928e-05;
                  } else {
                    result[0] += -4.769549473418335e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8323869080904523488) ) ) {
                  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.6350000000000001199) ) ) {
                    result[0] += 0.0012887394110453418;
                  } else {
                    result[0] += -0.000607624444212941;
                  }
                } else {
                  result[0] += -0.0002808996495439047;
                }
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2250000000000000333) ) ) {
                result[0] += -3.680868307145939e-05;
              } else {
                result[0] += 0.0005959368912012391;
              }
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0005965000000000001334) ) ) {
            result[0] += 1.7750228353665717e-07;
          } else {
            result[0] += -0.00025030798508195195;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 2.3077298057495073e-05;
      } else {
        result[0] += 2.3077298057495073e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            result[0] += 2.3077298057495073e-05;
          } else {
            result[0] += 2.3077298057495073e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 2.3077298057495073e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              result[0] += 2.3077298057495073e-05;
            } else {
              result[0] += 2.3077298057495073e-05;
            }
          }
        }
      } else {
        result[0] += 2.3077298057495073e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
          result[0] += 1.4529364377143529e-06;
        } else {
          result[0] += -3.321697068665221e-05;
        }
      } else {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6722423356281408413) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.527988611169282529) ) ) {
              result[0] += 1.348956006433157e-05;
            } else {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.04500000000000000527) ) ) {
                result[0] += 0.0003316128912945994;
              } else {
                result[0] += -0.0009842965418281884;
              }
            }
          } else {
            if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.482877277201360311) ) ) {
              if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1995315939937592209) ) ) {
                result[0] += 0.0027781055044215947;
              } else {
                if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.545000000000000151) ) ) {
                  result[0] += -0.0018727456016343583;
                } else {
                  result[0] += -7.477513719505594e-05;
                }
              }
            } else {
              if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.606193063154585432) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6055650374709939943) ) ) {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.009189500000000001487) ) ) {
                    result[0] += 0.00048578174009304806;
                  } else {
                    result[0] += 0.0007997213695675279;
                  }
                } else {
                  result[0] += 0.00473539553319931;
                }
              } else {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7240686518592965859) ) ) {
                  result[0] += 6.030922751563993e-06;
                } else {
                  result[0] += 0.0007499509802751081;
                }
              }
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.735388073517588059) ) ) {
            result[0] += -0.0006663265905539666;
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8145641537437187107) ) ) {
              result[0] += -3.5411624228970404e-05;
            } else {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.006138500000000000727) ) ) {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8168185667587940513) ) ) {
                  result[0] += 0.0008018255086973792;
                } else {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8517455601758795458) ) ) {
                    result[0] += -4.262996808531304e-05;
                  } else {
                    result[0] += 0.000602627366231309;
                  }
                }
              } else {
                result[0] += 0.002090677777226971;
              }
            }
          }
        }
      }
    } else {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7211657179899498837) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
          result[0] += -5.18235428818338e-05;
        } else {
          result[0] += -0.0006804494840019356;
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -3.321697068665221e-05;
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  result[0] += -3.525451833607849e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                    result[0] += 4.3574074161116714e-05;
                  } else {
                    result[0] += -4.568165860186355e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8449888203266332498) ) ) {
                  result[0] += 0.0003844051796849924;
                } else {
                  result[0] += -0.00046852343016191085;
                }
              }
            } else {
              result[0] += -3.525451833607849e-05;
            }
          }
        } else {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0005965000000000001334) ) ) {
            result[0] += 1.700076445954407e-07;
          } else {
            result[0] += -0.0002397392874014784;
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 2.2102910499015456e-05;
      } else {
        result[0] += 2.2102910499015456e-05;
      }
    } else {
      result[0] += 2.2102910499015456e-05;
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 1.3915894297308802e-06;
      } else {
        result[0] += -3.1814458014379946e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6722423356281408413) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.527988611169282529) ) ) {
              result[0] += 1.2919993407816153e-05;
            } else {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.04500000000000000527) ) ) {
                result[0] += 0.0003176112748703654;
              } else {
                result[0] += -0.0009427368106230022;
              }
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.008813500000000001888) ) ) {
              if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.482877277201360311) ) ) {
                if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.29500000000000004) ) ) {
                  result[0] += -0.0015066444056454358;
                } else {
                  result[0] += 2.2050898563815183e-05;
                }
              } else {
                result[0] += 0.0001828636820873585;
              }
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6800105846231156992) ) ) {
                result[0] += 0.002124908175083913;
              } else {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7240686518592965859) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7210440605025126848) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7077536600502513098) ) ) {
                      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.04308950000000000974) ) ) {
                        if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.8550000000000000933) ) ) {
                          result[0] += -0.001982281506196104;
                        } else {
                          result[0] += 0.00015487410009573397;
                        }
                      } else {
                        result[0] += 0.0006133775464965193;
                      }
                    } else {
                      result[0] += 0.0012449471672235145;
                    }
                  } else {
                    result[0] += -0.0004029754436097173;
                  }
                } else {
                  result[0] += 0.0017392181699634867;
                }
              }
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.735388073517588059) ) ) {
            result[0] += -0.0006381924329891573;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7403451809045227261) ) ) {
              result[0] += 0.0004842885605324473;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.013855723816631915) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9567162861906464144) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9310018456912946272) ) ) {
                    result[0] += -7.05975444588023e-05;
                  } else {
                    result[0] += 0.0010085253611440727;
                  }
                } else {
                  result[0] += -0.0004018365924432804;
                }
              } else {
                if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.114862829452247572) ) ) {
                  result[0] += 0.0004340890027181709;
                } else {
                  if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.145614105386054682) ) ) {
                    result[0] += -0.00033609544380234195;
                  } else {
                    result[0] += 1.8046677990080307e-05;
                  }
                }
              }
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6735883055778896233) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -4.963540910228284e-05;
          } else {
            result[0] += -0.0009681315184311864;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                result[0] += -3.376597474829508e-05;
              } else {
                result[0] += -3.61013826847581e-05;
              }
            } else {
              result[0] += -3.376597474829508e-05;
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 1.6282945010631828e-07;
            } else {
              result[0] += -0.0004613971306905791;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 2.11696642869708e-05;
      } else {
        result[0] += 2.11696642869708e-05;
      }
    } else {
      result[0] += 2.11696642869708e-05;
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 1.332832662649118e-06;
      } else {
        result[0] += -3.0471163318799175e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02126700000000000465) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.212199032544347022) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.004655500000000000783) ) ) {
                result[0] += 0.00010628784754972194;
              } else {
                result[0] += 0.0019910431175140086;
              }
            } else {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1450000000000000455) ) ) {
                result[0] += -3.524850680690557e-05;
              } else {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.6652304509807559496) ) ) {
                  result[0] += -0.00045192817239636795;
                } else {
                  result[0] += 2.0358101125415005e-05;
                }
              }
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7683067979899498301) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7664523331407036011) ) ) {
                  result[0] += 0.00013041379778289328;
                } else {
                  result[0] += 0.0014461840543190357;
                }
              } else {
                result[0] += -0.0003400349599113235;
              }
            } else {
              result[0] += 0.0021919867954322855;
            }
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            result[0] += -9.414256491645143e-05;
          } else {
            result[0] += -2.66958800633428e-05;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
            result[0] += -0.0007109994158198716;
          } else {
            result[0] += -4.753966440250069e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  result[0] += -3.2340281601173165e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                    result[0] += 4.315994898856098e-05;
                  } else {
                    result[0] += -4.2327159071886404e-05;
                  }
                }
              } else {
                result[0] += -3.457708213431001e-05;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2250000000000000333) ) ) {
                result[0] += -3.2340281601173165e-05;
              } else {
                result[0] += 0.0005736890187941408;
              }
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 1.8052698524078436e-06;
            } else {
              result[0] += -0.0002099970081864555;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 2.0275822319551392e-05;
      } else {
        result[0] += 2.0275822319551392e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 2.0275822319551392e-05;
            } else {
              result[0] += 2.0275822319551392e-05;
            }
          } else {
            result[0] += 2.0275822319551392e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 2.0275822319551392e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 2.0275822319551392e-05;
              } else {
                result[0] += 2.0275822319551392e-05;
              }
            } else {
              result[0] += 2.0275822319551392e-05;
            }
          }
        }
      } else {
        result[0] += 2.0275822319551392e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 1.2765567693108295e-06;
      } else {
        result[0] += -2.918458625261698e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6722423356281408413) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.527988611169282529) ) ) {
              result[0] += 1.1097776127797178e-05;
            } else {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.04500000000000000527) ) ) {
                result[0] += 0.00030568913530734925;
              } else {
                result[0] += -0.0009084382790008997;
              }
            }
          } else {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.008813500000000001888) ) ) {
              if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.482877277201360311) ) ) {
                result[0] += -0.0007675372469180911;
              } else {
                result[0] += 0.0001766309597869558;
              }
            } else {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6800105846231156992) ) ) {
                if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9750000000000000888) ) ) {
                  result[0] += 0.0033909095706929483;
                } else {
                  result[0] += -2.2067562942119542e-05;
                }
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.803731059838205808) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
                    if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5850000000000000755) ) ) {
                      result[0] += -0.00014259927258099338;
                    } else {
                      result[0] += 0.0003518431812073699;
                    }
                  } else {
                    result[0] += -0.0003919124778731873;
                  }
                } else {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7136104594723619021) ) ) {
                    result[0] += -0.0011259586079965026;
                  } else {
                    result[0] += 0.0028547905616743727;
                  }
                }
              }
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.735388073517588059) ) ) {
            result[0] += -0.0006097578878585723;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7403451809045227261) ) ) {
              result[0] += 0.0004641549108339154;
            } else {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.013855723816631915) ) ) {
                result[0] += -7.501089661652944e-05;
              } else {
                if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.114862829452247572) ) ) {
                  result[0] += 0.0004165358100834525;
                } else {
                  if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.145614105386054682) ) ) {
                    if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.545000000000000151) ) ) {
                      result[0] += -0.0006483013556955033;
                    } else {
                      result[0] += 0.00031466538499028883;
                    }
                  } else {
                    result[0] += 1.4065913272805672e-05;
                  }
                }
              }
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          result[0] += -4.553240785917986e-05;
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                result[0] += -3.097478517471168e-05;
              } else {
                result[0] += -3.311714178270494e-05;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2250000000000000333) ) ) {
                result[0] += -3.097478517471168e-05;
              } else {
                result[0] += 0.0005494662765581811;
              }
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 1.7290463500072913e-06;
            } else {
              result[0] += -0.00020113035180471865;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.9419720840214784e-05;
      } else {
        result[0] += 1.9419720840214784e-05;
      }
    } else {
      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8011796369346734226) ) ) {
        result[0] += 1.9419720840214784e-05;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
          result[0] += -0.00042270412561789855;
        } else {
          result[0] += 1.9419720840214784e-05;
        }
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 1.2226570003426446e-06;
      } else {
        result[0] += -2.7952332040140967e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8643464628140704598) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02741500000000000534) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.2635054734422110356) ) ) {
                result[0] += 0.0004803626455535596;
              } else {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8168185667587940513) ) ) {
                  if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8145641537437187107) ) ) {
                    result[0] += -2.2090835382126206e-05;
                  } else {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002740500000000000314) ) ) {
                      result[0] += 0.0006793484310747425;
                    } else {
                      result[0] += 0.005900122853853099;
                    }
                  }
                } else {
                  result[0] += -4.06976054880919e-05;
                }
              }
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7593447680904524821) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6722423356281408413) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.527988611169282529) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5926917132914574227) ) ) {
                      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.2273413669989351737) ) ) {
                        result[0] += 0.0001262833964998326;
                      } else {
                        result[0] += -0.0012913852908836255;
                      }
                    } else {
                      result[0] += 0.0005358567504338024;
                    }
                  } else {
                    if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.013855723816631915) ) ) {
                      result[0] += -0.0012055931989273564;
                    } else {
                      result[0] += 0.00430064124652147;
                    }
                  }
                } else {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7210440605025126848) ) ) {
                    result[0] += 0.0009342241677185001;
                  } else {
                    result[0] += 0.00023039700079681644;
                  }
                }
              } else {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
                  if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9284011333411857914) ) ) {
                    result[0] += 0.0009175531976104941;
                  } else {
                    result[0] += -0.0003862416184370163;
                  }
                } else {
                  result[0] += 0.0020495179831880673;
                }
              }
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
              result[0] += -9.06361835025417e-05;
            } else {
              result[0] += -2.603728483383509e-05;
            }
          }
        } else {
          result[0] += 0.0011788103102432677;
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          result[0] += -4.360990325681915e-05;
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  result[0] += -2.9666943796331513e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                    result[0] += 4.264545756115624e-05;
                  } else {
                    result[0] += -3.923214758881454e-05;
                  }
                }
              } else {
                result[0] += -3.17188441637624e-05;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2250000000000000333) ) ) {
                result[0] += -2.9666943796331513e-05;
              } else {
                result[0] += 0.0005262662857122741;
              }
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 1.6560412153817605e-06;
            } else {
              result[0] += -0.00019263807025846514;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.8599766340833076e-05;
      } else {
        result[0] += 1.8599766340833076e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        result[0] += 1.8599766340833076e-05;
      } else {
        result[0] += 1.8599766340833076e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9189305784170854752) ) ) {
      if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
          result[0] += 1.171033029180425e-06;
        } else {
          result[0] += -2.6772107019753594e-05;
        }
      } else {
        if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02972700000000000342) ) ) {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.212199032544347022) ) ) {
                result[0] += 0.0004987623444613432;
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.045304313006248043) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.8030059940338053481) ) ) {
                    result[0] += -8.667792464426344e-06;
                  } else {
                    if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9033411549107539518) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7640286906783920751) ) ) {
                        result[0] += -0.0003267291563183922;
                      } else {
                        result[0] += 0.0001495117804989987;
                      }
                    } else {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7801862323115579256) ) ) {
                        result[0] += 0.00012738373915030974;
                      } else {
                        result[0] += -0.0002494510078489912;
                      }
                    }
                  }
                } else {
                  if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.114862829452247572) ) ) {
                    result[0] += 0.0007288138843120365;
                  } else {
                    result[0] += -3.342138256369248e-05;
                  }
                }
              }
            } else {
              result[0] += 0.00010664770738998435;
            }
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
              result[0] += -8.680927233933655e-05;
            } else {
              result[0] += -2.4937918420337244e-05;
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
            if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
              result[0] += -0.0006772152118890679;
            } else {
              result[0] += -4.176857213330297e-05;
            }
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
              if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  result[0] += -2.841432310992244e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                    result[0] += 4.084484801103836e-05;
                  } else {
                    result[0] += -3.7575657456923035e-05;
                  }
                }
              } else {
                result[0] += -3.0379586550262772e-05;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                result[0] += 1.5861185601135176e-06;
              } else {
                result[0] += -0.00119024611170847;
              }
            }
          }
        }
      }
    } else {
      if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
        result[0] += -2.841432310992244e-05;
      } else {
        result[0] += -0.0006483416671423418;
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.781443259560745e-05;
      } else {
        result[0] += 1.781443259560745e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.781443259560745e-05;
            } else {
              result[0] += 1.781443259560745e-05;
            }
          } else {
            result[0] += 1.781443259560745e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.781443259560745e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.781443259560745e-05;
              } else {
                result[0] += 1.781443259560745e-05;
              }
            } else {
              result[0] += 1.781443259560745e-05;
            }
          }
        }
      } else {
        result[0] += 1.781443259560745e-05;
      }
    }
  }
}

