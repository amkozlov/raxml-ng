
#include "header.h"

void predict_unit10(union Entry* data, double* result) {
  unsigned int tmp;
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 1.1215887653259815e-06;
      } else {
        result[0] += -2.564171437459518e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.07584250000000002101) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8643464628140704598) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8168185667587940513) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8145641537437187107) ) ) {
                result[0] += -1.0992924201686817e-05;
              } else {
                result[0] += 0.0010921429931781616;
              }
            } else {
              result[0] += -3.756809614844591e-05;
            }
          } else {
            result[0] += 0.0009339000092080821;
          }
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9993516786272610419) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6384764007788945595) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6754021834779359024) ) ) {
                  result[0] += 6.011615681401396e-05;
                } else {
                  result[0] += -0.0032031306358951657;
                }
              } else {
                result[0] += 0.00035729813043045873;
              }
            } else {
              result[0] += -0.0004009745188953637;
            }
          } else {
            result[0] += 0.002277752385317195;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
            result[0] += -0.0006486213065179306;
          } else {
            result[0] += -4.000498711911575e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  result[0] += -2.7214591544644e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                    result[0] += 3.912026519242703e-05;
                  } else {
                    result[0] += -3.5989108934800454e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8323869080904523488) ) ) {
                  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5950000000000000844) ) ) {
                    result[0] += 0.0012678974195407524;
                  } else {
                    result[0] += -0.0005411034834190735;
                  }
                } else {
                  result[0] += -0.0002463287962339895;
                }
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2250000000000000333) ) ) {
                result[0] += -2.7214591544644e-05;
              } else {
                result[0] += 0.0005314206470489304;
              }
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 1.5191482333708873e-06;
            } else {
              result[0] += -0.0001342488628924581;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.7062257820237202e-05;
      } else {
        result[0] += 1.7062257820237202e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.7062257820237202e-05;
            } else {
              result[0] += 1.7062257820237202e-05;
            }
          } else {
            result[0] += 1.7062257820237202e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.7062257820237202e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.7062257820237202e-05;
              } else {
                result[0] += 1.7062257820237202e-05;
              }
            } else {
              result[0] += 1.7062257820237202e-05;
            }
          }
        }
      } else {
        result[0] += 1.7062257820237202e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 1.0742321754885976e-06;
      } else {
        result[0] += -2.4559050043509504e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02170000000000000401) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.2635054734422110356) ) ) {
              result[0] += 0.00037991681261623895;
            } else {
              result[0] += -2.001202394652508e-05;
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7579047064321609017) ) ) {
                if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6722423356281408413) ) ) {
                  if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.527988611169282529) ) ) {
                    result[0] += 0.00013528479444995024;
                  } else {
                    result[0] += -0.0010060301120395744;
                  }
                } else {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6828811456281408399) ) ) {
                    result[0] += 0.0017491937701820672;
                  } else {
                    result[0] += 0.00025250466686613736;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9284011333411857914) ) ) {
                  result[0] += 0.0005371896061511477;
                } else {
                  result[0] += -0.0003575061308952154;
                }
              }
            } else {
              result[0] += 0.0019538970112708658;
            }
          }
        } else {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01173150000000000061) ) ) {
            result[0] += 2.600166832036821e-05;
          } else {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
              result[0] += -6.738781036413013e-05;
            } else {
              result[0] += -3.9759608344782566e-05;
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
            result[0] += -0.0006212347151734419;
          } else {
            result[0] += -3.8315865557793016e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  result[0] += -2.6065515975046227e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                    result[0] += 3.7468499045760365e-05;
                  } else {
                    result[0] += -3.446954889360958e-05;
                  }
                }
              } else {
                result[0] += -2.592708139700758e-05;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2250000000000000333) ) ) {
                result[0] += -2.6065515975046227e-05;
              } else {
                result[0] += 0.0005089825927536076;
              }
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 1.4550055796514474e-06;
            } else {
              result[0] += -0.00012858050338969114;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.6341841951004082e-05;
      } else {
        result[0] += 1.6341841951004082e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            result[0] += 1.6341841951004082e-05;
          } else {
            result[0] += 1.6341841951004082e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.6341841951004082e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.6341841951004082e-05;
              } else {
                result[0] += 1.6341841951004082e-05;
              }
            } else {
              result[0] += 1.6341841951004082e-05;
            }
          }
        }
      } else {
        result[0] += 1.6341841951004082e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 1.0288751122783896e-06;
      } else {
        result[0] += -2.3522098804640738e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.07584250000000002101) ) ) {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.29500000000000004) ) ) {
            result[0] += -3.070112411195593e-05;
          } else {
            result[0] += 1.502752997484567e-05;
          }
        } else {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9993516786272610419) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6384764007788945595) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6754021834779359024) ) ) {
                  result[0] += 5.230220967211609e-05;
                } else {
                  result[0] += -0.0030254081896101486;
                }
              } else {
                result[0] += 0.00034258671226319084;
              }
            } else {
              result[0] += -0.00037303471287605805;
            }
          } else {
            result[0] += 0.0020990804058849174;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
            result[0] += -0.0005950044617073624;
          } else {
            result[0] += -3.669806339573494e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.055261500000000012) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
                      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0008885000000000000753) ) ) {
                        result[0] += -2.49649575644321e-05;
                      } else {
                        result[0] += 0.0068972337033448355;
                      }
                    } else {
                      result[0] += -2.49649575644321e-05;
                    }
                  } else {
                    result[0] += 0.00011564388233760216;
                  }
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                    result[0] += 3.58864750490984e-05;
                  } else {
                    result[0] += -3.3014148893806985e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.394135022639764854) ) ) {
                  result[0] += -0.0011070977528561457;
                } else {
                  result[0] += 0.0001251988757539511;
                }
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2250000000000000333) ) ) {
                result[0] += -2.49649575644321e-05;
              } else {
                result[0] += 0.0004874919353713618;
              }
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 1.3935712067539803e-06;
            } else {
              result[0] += -0.00012315147775359794;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.5651844038770136e-05;
      } else {
        result[0] += 1.5651844038770136e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.5651844038770136e-05;
            } else {
              result[0] += 1.5651844038770136e-05;
            }
          } else {
            result[0] += 1.5651844038770136e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.5651844038770136e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.5651844038770136e-05;
              } else {
                result[0] += 1.5651844038770136e-05;
              }
            } else {
              result[0] += 1.5651844038770136e-05;
            }
          }
        }
      } else {
        result[0] += 1.5651844038770136e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 9.854331501329612e-07;
      } else {
        result[0] += -2.2528930524391548e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02972700000000000342) ) ) {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.2635054734422110356) ) ) {
              result[0] += 0.0003670837830398064;
            } else {
              result[0] += -1.413469026401831e-05;
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.786764172562814168) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.166246961251310221) ) ) {
                  result[0] += 0.00012440175711644243;
                } else {
                  result[0] += -0.0018348867760205564;
                }
              } else {
                result[0] += -0.00032666066937896057;
              }
            } else {
              result[0] += 0.0018710187429963727;
            }
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            result[0] += -8.928357917940691e-05;
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.008191000000000002099) ) ) {
              result[0] += 4.3684609798447235e-05;
            } else {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.038794232605861678) ) ) {
                result[0] += -4.575431780566474e-05;
              } else {
                result[0] += -2.9626714211436026e-05;
              }
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
            result[0] += -0.0005698817223258797;
          } else {
            result[0] += -3.514856933000871e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.055261500000000012) ) ) {
                    result[0] += -2.391086778372475e-05;
                  } else {
                    result[0] += 0.0001107610767386429;
                  }
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                    result[0] += 3.437124849534862e-05;
                  } else {
                    result[0] += -3.1620199920415074e-05;
                  }
                }
              } else {
                result[0] += -2.199938703535084e-05;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2250000000000000333) ) ) {
                result[0] += -2.391086778372475e-05;
              } else {
                result[0] += 0.0004669086731757038;
              }
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 1.3347307635472906e-06;
            } else {
              result[0] += -0.00011795168064422803;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.499097975298583e-05;
      } else {
        result[0] += 1.499097975298583e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.499097975298583e-05;
            } else {
              result[0] += 1.499097975298583e-05;
            }
          } else {
            result[0] += 1.499097975298583e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.499097975298583e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.499097975298583e-05;
              } else {
                result[0] += 1.499097975298583e-05;
              }
            } else {
              result[0] += 1.499097975298583e-05;
            }
          }
        }
      } else {
        result[0] += 1.499097975298583e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 9.438254281713339e-07;
      } else {
        result[0] += -2.1577696564760875e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
        if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.1450000000000000455) ) ) {
          if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.03500000000000001027) ) ) {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.1811070000000000457) ) ) {
                result[0] += -9.832476168995543e-06;
              } else {
                result[0] += 0.0006028975758150943;
              }
            } else {
              result[0] += 0.0001703407889964418;
            }
          } else {
            result[0] += -0.0003415911472761972;
          }
        } else {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
            result[0] += 3.7211251117652565e-05;
          } else {
            if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
              result[0] += -8.551377872390175e-05;
            } else {
              result[0] += -2.15167773172469e-05;
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
            result[0] += -0.0005458197347112301;
          } else {
            result[0] += -3.366449920324705e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.055261500000000012) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
                      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0008885000000000000753) ) ) {
                        result[0] += -2.2901284598429147e-05;
                      } else {
                        result[0] += 0.006607022941248862;
                      }
                    } else {
                      result[0] += -2.2901284598429147e-05;
                    }
                  } else {
                    result[0] += 0.00010608443674079709;
                  }
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                    result[0] += 3.2919999011122864e-05;
                  } else {
                    result[0] += -3.028510734058552e-05;
                  }
                }
              } else {
                result[0] += -2.1070511871195986e-05;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2250000000000000333) ) ) {
                result[0] += -2.2901284598429147e-05;
              } else {
                result[0] += 0.00044719449342402846;
              }
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 1.2783747271222423e-06;
            } else {
              result[0] += -0.00011297143339712376;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.4358018991100366e-05;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          result[0] += 1.4358018991100366e-05;
        } else {
          result[0] += 1.4358018991100366e-05;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.4358018991100366e-05;
            } else {
              result[0] += 1.4358018991100366e-05;
            }
          } else {
            result[0] += 1.4358018991100366e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.4358018991100366e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.4358018991100366e-05;
              } else {
                result[0] += 1.4358018991100366e-05;
              }
            } else {
              result[0] += 1.4358018991100366e-05;
            }
          }
        }
      } else {
        result[0] += 1.4358018991100366e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 9.039744996832752e-07;
      } else {
        result[0] += -2.0666626342373503e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6722423356281408413) ) ) {
            result[0] += -5.922776028245141e-06;
          } else {
            if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.482877277201360311) ) ) {
              result[0] += -0.0008270045805154659;
            } else {
              if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.606193063154585432) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6055650374709939943) ) ) {
                  result[0] += 0.0005124672881059585;
                } else {
                  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.875000000000000111) ) ) {
                    result[0] += 0.006053289903410086;
                  } else {
                    result[0] += -0.00018923134747047407;
                  }
                }
              } else {
                result[0] += 4.635816851633592e-05;
              }
            }
          }
        } else {
          if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.735388073517588059) ) ) {
            result[0] += -0.0005780509761491432;
          } else {
            result[0] += -9.417321742153913e-06;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
            result[0] += -0.0005227737109804626;
          } else {
            result[0] += -3.224309063520967e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.055261500000000012) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
                      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.0008885000000000000753) ) ) {
                        result[0] += -2.1934328816590872e-05;
                      } else {
                        result[0] += 0.006328056099615144;
                      }
                    } else {
                      result[0] += -2.1934328816590872e-05;
                    }
                  } else {
                    result[0] += 0.00010160525746032095;
                  }
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                    result[0] += 3.1530025307023354e-05;
                  } else {
                    result[0] += -2.9006386074068412e-05;
                  }
                }
              } else {
                result[0] += -2.018085639389949e-05;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2250000000000000333) ) ) {
                result[0] += -2.1934328816590872e-05;
              } else {
                result[0] += 0.00042831270104403925;
              }
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 1.2243981989308252e-06;
            } else {
              result[0] += -0.00010820146600789707;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.3751783588911638e-05;
      } else {
        result[0] += 1.3751783588911638e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.3751783588911638e-05;
            } else {
              result[0] += 1.3751783588911638e-05;
            }
          } else {
            result[0] += 1.3751783588911638e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.3751783588911638e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.3751783588911638e-05;
              } else {
                result[0] += 1.3751783588911638e-05;
              }
            } else {
              result[0] += 1.3751783588911638e-05;
            }
          }
        }
      } else {
        result[0] += 1.3751783588911638e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 8.658061879736408e-07;
      } else {
        result[0] += -1.979402403279741e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
        if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.08005850000000001854) ) ) {
          result[0] += -1.0396500247266276e-05;
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9993516786272610419) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6384764007788945595) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.6754021834779359024) ) ) {
                result[0] += 7.23216687739466e-05;
              } else {
                result[0] += -0.0028882466462496603;
              }
            } else {
              result[0] += 0.0003507298390205518;
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7974125133417085953) ) ) {
              result[0] += -0.00035495968896285016;
            } else {
              result[0] += 0.0014880136750865935;
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
            result[0] += -0.0005007007543193202;
          } else {
            result[0] += -3.088169788101499e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.055261500000000012) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
                      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000924500000000000083) ) ) {
                        result[0] += -2.1008200590954165e-05;
                      } else {
                        result[0] += 0.0067262111600300805;
                      }
                    } else {
                      result[0] += -2.1008200590954165e-05;
                    }
                  } else {
                    result[0] += 9.731520155781657e-05;
                  }
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                    result[0] += 3.0198740149586173e-05;
                  } else {
                    result[0] += -2.778165596759755e-05;
                  }
                }
              } else {
                result[0] += -1.9328764639454864e-05;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2250000000000000333) ) ) {
                result[0] += -2.1008200590954165e-05;
              } else {
                result[0] += 0.0004102281503312066;
              }
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 1.1727007095327962e-06;
            } else {
              result[0] += -0.00010363289987746741;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.3171145127575913e-05;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            result[0] += 1.3171145127575913e-05;
          } else {
            result[0] += 1.3171145127575913e-05;
          }
        } else {
          result[0] += 1.3171145127575913e-05;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.3171145127575913e-05;
            } else {
              result[0] += 1.3171145127575913e-05;
            }
          } else {
            result[0] += 1.3171145127575913e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.3171145127575913e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.3171145127575913e-05;
              } else {
                result[0] += 1.3171145127575913e-05;
              }
            } else {
              result[0] += 1.3171145127575913e-05;
            }
          }
        }
      } else {
        result[0] += 1.3171145127575913e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 8.292494482932177e-07;
      } else {
        result[0] += -1.8958265414013583e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.02972700000000000342) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.394173313988213314) ) ) {
              result[0] += 0.0008536711122358668;
            } else {
              result[0] += -1.320888157352964e-05;
            }
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7579047064321609017) ) ) {
              result[0] += 0.0001184770688908435;
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7974125133417085953) ) ) {
                result[0] += -0.00028455456777509133;
              } else {
                result[0] += 0.0010194284229451901;
              }
            }
          }
        } else {
          if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01173150000000000061) ) ) {
            result[0] += 2.711776697245634e-05;
          } else {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
              result[0] += -6.164759661211006e-05;
            } else {
              result[0] += -3.58668861186274e-05;
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
            result[0] += -0.00047955977913607375;
          } else {
            result[0] += -2.9577786906471734e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.055261500000000012) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
                      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000924500000000000083) ) ) {
                        result[0] += -2.012117606880859e-05;
                      } else {
                        result[0] += 0.006442211861077988;
                      }
                    } else {
                      result[0] += -2.012117606880859e-05;
                    }
                  } else {
                    result[0] += 9.320628371948962e-05;
                  }
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                    result[0] += 2.8923665545523262e-05;
                  } else {
                    result[0] += -2.6608637364582024e-05;
                  }
                }
              } else {
                result[0] += -1.8512650563252017e-05;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2250000000000000333) ) ) {
                result[0] += -2.012117606880859e-05;
              } else {
                result[0] += 0.00039290717953017177;
              }
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 1.1231860315864608e-06;
            } else {
              result[0] += -9.92572312858436e-05;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.2615022833222431e-05;
      } else {
        result[0] += 1.2615022833222431e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.2615022833222431e-05;
            } else {
              result[0] += 1.2615022833222431e-05;
            }
          } else {
            result[0] += 1.2615022833222431e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.2615022833222431e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.2615022833222431e-05;
              } else {
                result[0] += 1.2615022833222431e-05;
              }
            } else {
              result[0] += 1.2615022833222431e-05;
            }
          }
        }
      } else {
        result[0] += 1.2615022833222431e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 7.942362355991222e-07;
      } else {
        result[0] += -1.8157794843163505e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.07794150000000001077) ) ) {
            result[0] += -5.195078460524473e-06;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9993516786272610419) ) ) {
              if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9310018456912946272) ) ) {
                result[0] += 0.00013334766363001736;
              } else {
                result[0] += 0.0017145574189233632;
              }
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8032211286180904741) ) ) {
                result[0] += -0.00032410485323034177;
              } else {
                result[0] += 0.001874545291249596;
              }
            }
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            result[0] += -8.82959161317325e-05;
          } else {
            result[0] += -1.8018004810367564e-05;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
            result[0] += -0.00045931143458667996;
          } else {
            result[0] += -2.8328930671343546e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.055261500000000012) ) ) {
                    if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
                      if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000924500000000000083) ) ) {
                        result[0] += -1.9271604183288465e-05;
                      } else {
                        result[0] += 0.006170203800564048;
                      }
                    } else {
                      result[0] += -1.9271604183288465e-05;
                    }
                  } else {
                    result[0] += 8.927085579365175e-05;
                  }
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                    result[0] += 2.770242812929908e-05;
                  } else {
                    result[0] += -2.5485146861857762e-05;
                  }
                }
              } else {
                result[0] += -1.7730995087886028e-05;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2250000000000000333) ) ) {
                result[0] += -1.9271604183288465e-05;
              } else {
                result[0] += 0.0003763175481782901;
              }
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 1.0757620007355009e-06;
            } else {
              result[0] += -9.506631556368849e-05;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.2082381565254028e-05;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          result[0] += 1.2082381565254028e-05;
        } else {
          result[0] += 1.2082381565254028e-05;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.2082381565254028e-05;
            } else {
              result[0] += 1.2082381565254028e-05;
            }
          } else {
            result[0] += 1.2082381565254028e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.2082381565254028e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.2082381565254028e-05;
              } else {
                result[0] += 1.2082381565254028e-05;
              }
            } else {
              result[0] += 1.2082381565254028e-05;
            }
          }
        }
      } else {
        result[0] += 1.2082381565254028e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 7.607013778990203e-07;
      } else {
        result[0] += -1.739112236094676e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.08005850000000001854) ) ) {
            result[0] += -4.711994497388568e-06;
          } else {
            if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.9993516786272610419) ) ) {
              result[0] += 0.00014245487544897552;
            } else {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7974125133417085953) ) ) {
                result[0] += -0.0003153589329230151;
              } else {
                result[0] += 0.001422707184566962;
              }
            }
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            result[0] += -8.45678175506556e-05;
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01173150000000000061) ) ) {
              result[0] += 4.174908166679874e-05;
            } else {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.038794232605861678) ) ) {
                result[0] += -5.8283893865301e-05;
              } else {
                result[0] += -2.5813037277522874e-05;
              }
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
            result[0] += -0.00043991803132892163;
          } else {
            result[0] += -2.713280461176738e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  result[0] += -1.845790358015253e-05;
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                    if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                      result[0] += 0.000829692015254374;
                    } else {
                      result[0] += 2.653275474545657e-05;
                    }
                  } else {
                    result[0] += -2.4409093245600738e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8323869080904523488) ) ) {
                  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.5950000000000000844) ) ) {
                    result[0] += 0.0010355767930359029;
                  } else {
                    result[0] += -0.0005174310797601155;
                  }
                } else {
                  result[0] += -0.0002910794666306245;
                }
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2250000000000000333) ) ) {
                result[0] += -1.845790358015253e-05;
              } else {
                result[0] += 0.00036042837709470966;
              }
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 1.030340344058458e-06;
            } else {
              result[0] += -9.1052351932204e-05;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.1572229889583646e-05;
      } else {
        result[0] += 1.1572229889583646e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.1572229889583646e-05;
            } else {
              result[0] += 1.1572229889583646e-05;
            }
          } else {
            result[0] += 1.1572229889583646e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.1572229889583646e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.1572229889583646e-05;
              } else {
                result[0] += 1.1572229889583646e-05;
              }
            } else {
              result[0] += 1.1572229889583646e-05;
            }
          }
        }
      } else {
        result[0] += 1.1572229889583646e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 7.285824549429521e-07;
      } else {
        result[0] += -1.6656820918278892e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8517455601758795458) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8490362337185931585) ) ) {
            result[0] += -8.268951521977217e-07;
          } else {
            result[0] += -3.101604250073858e-05;
          }
        } else {
          result[0] += 0.0006660741218990374;
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
            result[0] += -0.0004213434713691894;
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
              result[0] += -2.5987182313416642e-05;
            } else {
              result[0] += -0.0013290954661736272;
            }
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.000924500000000000083) ) ) {
                      result[0] += -1.7678559674323504e-05;
                    } else {
                      result[0] += 0.005916215438462966;
                    }
                  } else {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.055261500000000012) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9017068521859298302) ) ) {
                        result[0] += -1.7678559674323504e-05;
                      } else {
                        result[0] += -1.7678559674323504e-05;
                      }
                    } else {
                      result[0] += 8.628093646062983e-05;
                    }
                  }
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                    result[0] += 2.5412468217469573e-05;
                  } else {
                    result[0] += -2.3378473598837243e-05;
                  }
                }
              } else {
                result[0] += -1.3397713462744673e-05;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2250000000000000333) ) ) {
                result[0] += -1.7678559674323504e-05;
              } else {
                result[0] += 0.0003452100909032781;
              }
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 9.86836515761555e-07;
            } else {
              result[0] += -8.720786898311835e-05;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.108361823322066e-05;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            result[0] += 1.108361823322066e-05;
          } else {
            result[0] += 1.108361823322066e-05;
          }
        } else {
          result[0] += 1.108361823322066e-05;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.108361823322066e-05;
            } else {
              result[0] += 1.108361823322066e-05;
            }
          } else {
            result[0] += 1.108361823322066e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.108361823322066e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.108361823322066e-05;
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.3230417339964383738) ) ) {
                  result[0] += 1.108361823322066e-05;
                } else {
                  result[0] += -0.0010444847446695617;
                }
              }
            } else {
              result[0] += 1.108361823322066e-05;
            }
          }
        }
      } else {
        result[0] += 1.108361823322066e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 6.978196820371687e-07;
      } else {
        result[0] += -1.5953523720047552e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
        if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8517455601758795458) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8490362337185931585) ) ) {
            if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.08005850000000001854) ) ) {
              if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8168185667587940513) ) ) {
                result[0] += -4.663268763234129e-06;
              } else {
                result[0] += -3.0981128692958275e-05;
              }
            } else {
              result[0] += 6.997424611334387e-05;
            }
          } else {
            result[0] += -2.970645912357344e-05;
          }
        } else {
          result[0] += 0.0006379506242613852;
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
            result[0] += -0.00040355318087132846;
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.01500000000000000118) ) ) {
              result[0] += -2.4889931367355423e-05;
            } else {
              result[0] += -0.0012729773676404216;
            }
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                    result[0] += -1.693212183070871e-05;
                  } else {
                    result[0] += -0.0001995898486081475;
                  }
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                    if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                      result[0] += 0.0008053061661970511;
                    } else {
                      result[0] += 2.4339483295246076e-05;
                    }
                  } else {
                    result[0] += -2.2391369573305867e-05;
                  }
                }
              } else {
                result[0] += -1.2832024824600925e-05;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2250000000000000333) ) ) {
                result[0] += -1.693212183070871e-05;
              } else {
                result[0] += 0.00033063436298228936;
              }
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 9.451695398090258e-07;
            } else {
              result[0] += -8.352571077174861e-05;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.0615637116780344e-05;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            result[0] += 1.0615637116780344e-05;
          } else {
            result[0] += 1.0615637116780344e-05;
          }
        } else {
          result[0] += 1.0615637116780344e-05;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.0615637116780344e-05;
            } else {
              result[0] += 1.0615637116780344e-05;
            }
          } else {
            result[0] += 1.0615637116780344e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.0615637116780344e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.0615637116780344e-05;
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.3230417339964383738) ) ) {
                  result[0] += 1.0615637116780344e-05;
                } else {
                  result[0] += -0.0010003837005312173;
                }
              }
            } else {
              result[0] += 1.0615637116780344e-05;
            }
          }
        }
      } else {
        result[0] += 1.0615637116780344e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 6.68355798763468e-07;
      } else {
        result[0] += -1.5279921681022543e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01314200000000000264) ) ) {
            result[0] += -1.9347714055077544e-05;
          } else {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.7273815826884423297) ) ) {
              result[0] += 0.00010362356780452431;
            } else {
              result[0] += -0.00019401410788197167;
            }
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            result[0] += -8.23410211723094e-05;
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.01173150000000000061) ) ) {
              result[0] += 4.0218129548715424e-05;
            } else {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
                result[0] += -4.13482299887926e-05;
              } else {
                if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.2328444889043961574) ) ) {
                  result[0] += 2.6643099148137002e-05;
                } else {
                  result[0] += -3.349606712437698e-05;
                }
              }
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
            result[0] += -0.00038651404580248075;
          } else {
            result[0] += -2.3839009400870056e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                    result[0] += -1.621720066405429e-05;
                  } else {
                    result[0] += -0.00019116261138141507;
                  }
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                    result[0] += 2.3311802773739056e-05;
                  } else {
                    result[0] += -2.144594381873178e-05;
                  }
                }
              } else {
                result[0] += -1.2290221130423211e-05;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2250000000000000333) ) ) {
                result[0] += -1.621720066405429e-05;
              } else {
                result[0] += 0.000316674062738604;
              }
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 9.052618591980242e-07;
            } else {
              result[0] += -7.99990234972525e-05;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 1.0167415461621036e-05;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            result[0] += 1.0167415461621036e-05;
          } else {
            result[0] += 1.0167415461621036e-05;
          }
        } else {
          result[0] += 1.0167415461621036e-05;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 1.0167415461621036e-05;
            } else {
              result[0] += 1.0167415461621036e-05;
            }
          } else {
            result[0] += 1.0167415461621036e-05;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 1.0167415461621036e-05;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 1.0167415461621036e-05;
              } else {
                result[0] += 1.0167415461621036e-05;
              }
            } else {
              result[0] += 1.0167415461621036e-05;
            }
          }
        }
      } else {
        result[0] += 1.0167415461621036e-05;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 6.401359623974081e-07;
      } else {
        result[0] += -1.4634760989184549e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
          if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.07794150000000001077) ) ) {
            if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3750409390474713223) ) ) {
              if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3763018001168558224) ) ) {
                if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.4008331129359999911) ) ) {
                  result[0] += 0.00013131522348735548;
                } else {
                  result[0] += -0.0011379554224717993;
                }
              } else {
                result[0] += 0.0013371449601258223;
              }
            } else {
              if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.3715165125194505591) ) ) {
                result[0] += -0.0011459997271715914;
              } else {
                result[0] += -1.607513378043028e-05;
              }
            }
          } else {
            result[0] += 0.00010953544828543059;
          }
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            result[0] += -7.886435477995728e-05;
          } else {
            result[0] += -1.6413062694893253e-05;
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6731895574120604353) ) ) {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
            result[0] += -0.0003701943502961402;
          } else {
            result[0] += -2.283246027588999e-05;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  if ( LIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)1.00000001800250948e-35) ) ) {
                    result[0] += -1.5532465452807037e-05;
                  } else {
                    result[0] += -0.0001830911954941491;
                  }
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                    result[0] += 2.232751377544039e-05;
                  } else {
                    result[0] += -2.054043656286702e-05;
                  }
                }
              } else {
                result[0] += -1.1771293891599362e-05;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2250000000000000333) ) ) {
                result[0] += -1.5532465452807037e-05;
              } else {
                result[0] += 0.00030330320510800983;
              }
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 8.670391915975684e-07;
            } else {
              result[0] += -7.662124274527711e-05;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 9.738118968458881e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            result[0] += 9.738118968458881e-06;
          } else {
            result[0] += 9.738118968458881e-06;
          }
        } else {
          result[0] += 9.738118968458881e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 9.738118968458881e-06;
            } else {
              result[0] += 9.738118968458881e-06;
            }
          } else {
            result[0] += 9.738118968458881e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 9.738118968458881e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 9.738118968458881e-06;
              } else {
                result[0] += 9.738118968458881e-06;
              }
            } else {
              result[0] += 9.738118968458881e-06;
            }
          }
        }
      } else {
        result[0] += 9.738118968458881e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 6.131076458266819e-07;
      } else {
        result[0] += -1.4016840771936836e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
        if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9850000000000000977) ) ) {
          result[0] += 3.2487924973961907e-06;
        } else {
          if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.9950000000000001066) ) ) {
            result[0] += -7.553448288968385e-05;
          } else {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.008191000000000002099) ) ) {
              result[0] += 4.051738222407636e-05;
            } else {
              result[0] += -2.6380777136627302e-05;
            }
          }
        }
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -2.186841044792187e-05;
          } else {
            result[0] += -0.00044749872767391646;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002009500000000000435) ) ) {
                      result[0] += -1.4876641662170188e-05;
                    } else {
                      result[0] += 0.006019760733834724;
                    }
                  } else {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.055261500000000012) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9017068521859298302) ) ) {
                        result[0] += -1.4876641662170188e-05;
                      } else {
                        result[0] += -1.4876641662170188e-05;
                      }
                    } else {
                      result[0] += 8.469339608093455e-05;
                    }
                  }
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                    result[0] += 2.1384784189838158e-05;
                  } else {
                    result[0] += -1.9673162335930905e-05;
                  }
                }
              } else {
                result[0] += -2.0745105368305212e-05;
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2250000000000000333) ) ) {
                result[0] += -1.4876641662170188e-05;
              } else {
                result[0] += 0.00029049690218780613;
              }
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 8.304303910828077e-07;
            } else {
              result[0] += -7.338608126925835e-05;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 9.326948564446002e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            result[0] += 9.326948564446002e-06;
          } else {
            result[0] += 9.326948564446002e-06;
          }
        } else {
          result[0] += 9.326948564446002e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 9.326948564446002e-06;
            } else {
              result[0] += 9.326948564446002e-06;
            }
          } else {
            result[0] += 9.326948564446002e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 9.326948564446002e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 9.326948564446002e-06;
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.3230417339964383738) ) ) {
                  result[0] += 9.326948564446002e-06;
                } else {
                  result[0] += -0.0009589851917443907;
                }
              }
            } else {
              result[0] += 9.326948564446002e-06;
            }
          }
        }
      } else {
        result[0] += 9.326948564446002e-06;
      }
    }
  }
  if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.9950000000000001066) ) ) {
    if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)1.00000001800250948e-35) ) ) {
      if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5271332674874372737) ) ) {
        result[0] += 5.872205397792926e-07;
      } else {
        result[0] += -1.3425010860855756e-05;
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.355591326643301953) ) ) {
        result[0] += -8.022578567217923e-07;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.6665876335678392328) ) ) {
          if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
            result[0] += -2.094506547871953e-05;
          } else {
            result[0] += -0.0004286040896797121;
          }
        } else {
          if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.828053558455352334) ) ) {
            if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9330260472110553094) ) ) {
              if ( UNLIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.370731135743224804) ) ) {
                  if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.8430106374371860722) ) ) {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.002009500000000000435) ) ) {
                      result[0] += -1.424850857174266e-05;
                    } else {
                      result[0] += 0.0057655897321231536;
                    }
                  } else {
                    if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.055261500000000012) ) ) {
                      if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.9017068521859298302) ) ) {
                        result[0] += -1.424850857174266e-05;
                      } else {
                        result[0] += -1.424850857174266e-05;
                      }
                    } else {
                      result[0] += 8.111740589261142e-05;
                    }
                  }
                } else {
                  if ( LIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.003248500000000000519) ) ) {
                    if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)2.496729916098519464) ) ) {
                      result[0] += 0.0007684739617999137;
                    } else {
                      result[0] += 2.0481859263209975e-05;
                    }
                  } else {
                    result[0] += -1.8842506833353715e-05;
                  }
                }
              } else {
                if ( UNLIKELY( !(data[0].missing != -1) || (data[0].fvalue <= (double)0.02500000000000000486) ) ) {
                  result[0] += 0.00029012873561122727;
                } else {
                  if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.394135022639764854) ) ) {
                    result[0] += -0.0011846706685354259;
                  } else {
                    result[0] += 5.151014294765166e-05;
                  }
                }
              }
            } else {
              if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)0.2250000000000000333) ) ) {
                result[0] += -1.424850857174266e-05;
              } else {
                result[0] += 0.00027823131691160437;
              }
            }
          } else {
            if ( LIKELY( !(data[2].missing != -1) || (data[2].fvalue <= (double)1.00000001800250948e-35) ) ) {
              result[0] += 7.953673157072534e-07;
            } else {
              result[0] += -7.02875172876278e-05;
            }
          }
        }
      }
    }
  } else {
    if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.1464732738946245838) ) ) {
      if ( UNLIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-1.143279903388985774) ) ) {
        result[0] += 8.933138915796352e-06;
      } else {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.4100284358542713448) ) ) {
          if ( LIKELY(  (data[3].missing != -1) && (data[3].fvalue <= (double)-0.5470680148669562204) ) ) {
            result[0] += 8.933138915796352e-06;
          } else {
            result[0] += 8.933138915796352e-06;
          }
        } else {
          result[0] += 8.933138915796352e-06;
        }
      }
    } else {
      if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)1.064486481904431292) ) ) {
        if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5090080881909548882) ) ) {
          if ( LIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5072068278894473758) ) ) {
            if ( UNLIKELY( !(data[1].missing != -1) || (data[1].fvalue <= (double)0.03816150000000000792) ) ) {
              result[0] += 8.933138915796352e-06;
            } else {
              result[0] += 8.933138915796352e-06;
            }
          } else {
            result[0] += 8.933138915796352e-06;
          }
        } else {
          if ( UNLIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.1001961271985990637) ) ) {
            result[0] += 8.933138915796352e-06;
          } else {
            if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5613540176884422861) ) ) {
              if ( UNLIKELY( !(data[4].missing != -1) || (data[4].fvalue <= (double)0.5392784256532664466) ) ) {
                result[0] += 8.933138915796352e-06;
              } else {
                if ( LIKELY( !(data[3].missing != -1) || (data[3].fvalue <= (double)0.3230417339964383738) ) ) {
                  result[0] += 8.933138915796352e-06;
                } else {
                  result[0] += -0.0009184941759732421;
                }
              }
            } else {
              result[0] += 8.933138915796352e-06;
            }
          }
        }
      } else {
        result[0] += 8.933138915796352e-06;
      }
    }
  }
}

